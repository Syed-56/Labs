#Task 3
import heapq
import itertools
import json
import random
import sys
import argparse
# Packets and checksum
def inet_checksum(data: bytes) -> int:
    if len(data) % 2:
        data += b"\x00"
    s = 0
    for i in range(0, len(data), 2):
        s += (data[i] << 8) | data[i + 1]
        s = (s & 0xFFFF) + (s >> 16)
    return (~s) & 0xFFFF

class Pkt:
    __slots__ = ("kind", "seq", "payload", "chk", "dbg")

    def __init__(self, kind, seq, payload=b"", dbg=None):
        self.kind, self.seq, self.payload, self.dbg = kind, seq, payload, dbg
        self.chk = inet_checksum(self._bytes())

    def _bytes(self):
        return bytes([1 if self.kind == "DATA" else 2]) + self.seq.to_bytes(2, "big") + self.payload

    def ok(self):
        return self.chk == inet_checksum(self._bytes())

def corrupt(p: Pkt, rng: random.Random) -> Pkt:
    q = Pkt.__new__(Pkt)
    q.kind, q.seq, q.payload, q.chk, q.dbg = p.kind, p.seq, p.payload, p.chk, p.dbg
    fields = ["payload", "seq", "chk"] if p.payload else ["seq", "chk"]
    f = rng.choice(fields)
    if f == "payload":
        b = bytearray(p.payload)
        b[rng.randrange(len(b))] ^= 1 << rng.randrange(8)
        q.payload = bytes(b)
    elif f == "seq":
        q.seq = p.seq ^ (1 << rng.randrange(16))
    else:
        q.chk = p.chk ^ (1 << rng.randrange(16))
    return q


def payload_of(i: int) -> bytes:
    return f"RESCUE-MSG-{i:05d}".encode()

# Simulator core: clock, event heap, channel, logging, statistics
class Sim:
    def __init__(self, a):
        self.a = a
        self.M = 2 ** a.seq_bits                      # sequence-number space
        self.rng = random.Random(a.seed)
        self.t = 0.0                                  # virtual time (ms)
        self.q, self.cnt = [], itertools.count()
        self.tx_ms = a.pkt_bytes * 8 / a.rate * 1000  # L/R in ms
        self.prop = a.rtt / 2.0                       # one-way propagation delay
        self.link_free = 0.0                          # sender's link busy until
        self.last_arr = {"DATA": 0.0, "ACK": 0.0}     # FIFO link: nothing overtakes anything
        self.seen = set()                             # packets sent at least once
        self.drop_once = set(a.drop_first)            # scripted first-copy drops
        self.lines, self.out = [], []                 # log lines, delivered data
        self.done, self.finish = False, None
        self.st = dict(tx=0, retx=0, acks=0, timeouts=0, lost_data=0, lost_ack=0,
                       corrupt_data=0, corrupt_ack=0, delayed=0, discarded_ooo=0,
                       buffered=0)
        Snd, Rcv = (GBNSender, GBNReceiver) if a.protocol == "gbn" else (SRSender, SRReceiver)
        self.sender, self.receiver = Snd(self), Rcv(self)

    # infrastructure
    def at(self, time, fn, *args):
        heapq.heappush(self.q, (time, next(self.cnt), fn, args))

    def log(self, who, msg):
        line = f"[{self.t:10.3f} ms] {who:<8} {msg}"
        self.lines.append(line)
        if not self.a.quiet:
            print(line)

    # the unreliable channel (applies to DATA and ACK alike)
    def channel(self, pkt, depart, handler, forced_loss=False):
        a, r = self.a, self.rng
        lost = (r.random() < a.loss) or forced_loss
        corr = r.random() < a.corrupt
        dly = r.random() < a.delay
        extra = r.uniform(a.delay_min, a.delay_max) if dly else 0.0
        isdata = pkt.kind == "DATA"
        name = f"{pkt.kind} seq={pkt.seq}" + (f" (#{pkt.dbg})" if isdata else "")
        if lost:
            self.st["lost_data" if isdata else "lost_ack"] += 1
            self.log("CHANNEL", f"LOSS    {name}")
            return
        if corr:
            pkt = corrupt(pkt, r)
            self.st["corrupt_data" if isdata else "corrupt_ack"] += 1
            self.log("CHANNEL", f"CORRUPT {name}")
        if dly:
            self.st["delayed"] += 1
            self.log("CHANNEL", f"DELAY   {name} +{extra:.1f} ms")
        # One physical satellite path => FIFO. A delayed packet also holds up the packets behind it (no overtaking), so delay = jitter, never reordering.
        arr = max(depart + self.prop + extra, self.last_arr[pkt.kind])
        self.last_arr[pkt.kind] = arr
        self.at(arr, handler, pkt)

    #  helpers used by both senders / receivers 
    def send_data(self, i, retrans):
        """Put data packet #i on the link. Returns its departure time."""
        pkt = Pkt("DATA", i % self.M, payload_of(i), dbg=i)
        depart = max(self.t, self.link_free) + self.tx_ms   # serialisation delay L/R
        self.link_free = depart
        self.st["tx"] += 1
        if retrans:
            self.st["retx"] += 1
        first = i not in self.seen
        self.seen.add(i)
        self.log("SENDER", f"{'RETRANSMIT' if retrans else 'SEND'} DATA seq={pkt.seq} (#{i})")
        self.channel(pkt, depart, self.receiver.on_data, forced_loss=(first and i in self.drop_once))
        return depart

    def send_ack(self, seq):
        self.st["acks"] += 1
        self.log("RECEIVER", f"SEND ACK seq={seq}")
        self.channel(Pkt("ACK", seq), self.t, self.sender.on_ack)

    def complete(self):
        self.done, self.finish = True, self.t
        self.log("SENDER", "all packets acknowledged -> transfer complete")

    # main loop
    def run(self):
        self.sender.start()
        n = 0
        while self.q and not self.done:
            t, _, fn, args = heapq.heappop(self.q)
            if t > self.a.max_time or n > self.a.max_events:
                break
            self.t = t
            fn(*args)
            n += 1
        return self.summary()

    def summary(self):
        a = self.a
        expected = [payload_of(i) for i in range(a.packets)]
        correct = self.done and self.out == expected
        t_ms = self.finish if self.finish else self.t
        delivered = len(self.out)
        bits = delivered * a.pkt_bytes * 8
        res = dict(protocol=a.protocol.upper(), packets=a.packets, N=a.window, k=a.seq_bits,
                   loss=a.loss, corrupt=a.corrupt, delay=a.delay, seed=a.seed,
                   completed=self.done, in_order_correct=correct,
                   transmitted=self.st["tx"], retransmissions=self.st["retx"],
                   delivered=delivered, time_ms=round(t_ms, 3),
                   throughput_kbps=round(bits / t_ms, 3) if t_ms else 0.0,
                   utilization=round((delivered * self.tx_ms) / t_ms, 5) if t_ms else 0.0)
        res.update({k: v for k, v in self.st.items() if k not in ("tx", "retx")})
        return res

# Go-Back-N
class GBNSender:
    def __init__(self, sim):
        self.sim, self.base, self.nextseqnum, self.gen = sim, 0, 0, 0

    def start(self):
        self.try_send()

    def win(self):
        return f"base={self.base % self.sim.M}({self.base}) nextseqnum={self.nextseqnum % self.sim.M}({self.nextseqnum}) " f"window=[{self.base}..{self.base + self.sim.a.window - 1}]"

    def try_send(self):
        sm = self.sim
        while self.nextseqnum < self.base + sm.a.window and self.nextseqnum < sm.a.packets:
            d = sm.send_data(self.nextseqnum, False)
            if self.base == self.nextseqnum:
                self.start_timer(d)
            self.nextseqnum += 1

    def start_timer(self, frm):
        self.gen += 1
        self.sim.at(frm + self.sim.a.timeout, self.on_timeout, self.gen)

    def stop_timer(self):
        self.gen += 1                                  

    def on_timeout(self, g):
        sm = self.sim
        if g != self.gen:
            return
        sm.st["timeouts"] += 1
        sm.log("SENDER", f"TIMEOUT (oldest unACKed #{self.base}) -> go back, resend #{self.base}..#{self.nextseqnum - 1}")
        first = True
        for i in range(self.base, self.nextseqnum):
            d = sm.send_data(i, True)
            if first:
                self.start_timer(d)
                first = False

    def on_ack(self, pkt):
        sm = self.sim
        if not pkt.ok():
            sm.log("SENDER", "RECV ACK corrupted (checksum fail) -> ignored")
            return
        a_abs = self.base + (pkt.seq - self.base) % sm.M   
        if a_abs < self.nextseqnum:                       
            sm.log("SENDER", f"RECV ACK seq={pkt.seq} (cumulative up to #{a_abs})")
            self.base = a_abs + 1
            sm.log("SENDER", "window slides: " + self.win())
            if self.base >= sm.a.packets:
                self.stop_timer()
                sm.complete()
                return
            if self.base == self.nextseqnum:
                self.stop_timer()
            else:
                self.start_timer(sm.t)
            self.try_send()
        else:
            sm.log("SENDER", f"RECV ACK seq={pkt.seq} (duplicate) -> ignored")

class GBNReceiver:
    def __init__(self, sim):
        self.sim, self.expected = sim, 0

    def on_data(self, pkt):
        sm = self.sim
        if not pkt.ok():
            sm.log("RECEIVER", "RECV DATA corrupted (checksum fail) -> discard")
            return self.reack()
        if pkt.seq == self.expected % sm.M:
            sm.out.append(pkt.payload)
            sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} in order -> deliver (expectedseqnum={(self.expected + 1) % sm.M})")
            self.expected += 1
            sm.send_ack(pkt.seq)
        else:
            sm.st["discarded_ooo"] += 1
            sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} out of order (expectedseqnum={self.expected % sm.M}) -> discard")
            self.reack()

    def reack(self):
        if self.expected > 0:
            self.sim.send_ack((self.expected - 1) % self.sim.M)   # ACK of last in-order packet
        else:
            self.sim.log("RECEIVER", "nothing delivered yet -> no ACK")

# Selective Repeat
class SRSender:
    def __init__(self, sim):
        self.sim, self.base, self.nextseqnum = sim, 0, 0
        self.acked, self.gen = set(), {}

    def start(self):
        self.try_send()

    def win(self):
        sm = self.sim
        return f"send_base={self.base % sm.M}({self.base}) nextseqnum={self.nextseqnum % sm.M}({self.nextseqnum}) " \
               f"window=[{self.base}..{self.base + sm.a.window - 1}]"

    def try_send(self):
        sm = self.sim
        while self.nextseqnum < self.base + sm.a.window and self.nextseqnum < sm.a.packets:
            d = sm.send_data(self.nextseqnum, False)
            self.start_timer(self.nextseqnum, d)
            self.nextseqnum += 1

    def start_timer(self, i, frm):
        g = self.gen.get(i, 0) + 1
        self.gen[i] = g
        self.sim.at(frm + self.sim.a.timeout, self.on_timeout, i, g)

    def on_timeout(self, i, g):
        sm = self.sim
        if self.gen.get(i) != g or i in self.acked:
            return
        sm.st["timeouts"] += 1
        sm.log("SENDER", f"TIMEOUT for #{i} only -> selective retransmit")
        d = sm.send_data(i, True)
        self.start_timer(i, d)

    def on_ack(self, pkt):
        sm = self.sim
        if not pkt.ok():
            sm.log("SENDER", "RECV ACK corrupted (checksum fail) -> ignored")
            return
        i = self.base + (pkt.seq - self.base) % sm.M
        if i < self.nextseqnum and i not in self.acked:
            self.acked.add(i)
            self.gen[i] = self.gen.get(i, 0) + 1          # cancel that packet's timer
            sm.log("SENDER", f"RECV ACK seq={pkt.seq} (individual, #{i} marked ACKed)")
            if i == self.base:
                while self.base in self.acked:
                    self.base += 1
                sm.log("SENDER", "window slides: " + self.win())
            if self.base >= sm.a.packets:
                sm.complete()
                return
            self.try_send()
        else:
            sm.log("SENDER", f"RECV ACK seq={pkt.seq} (duplicate/stale) -> ignored")

class SRReceiver:
    def __init__(self, sim):
        self.sim, self.rcv_base, self.buf = sim, 0, {}

    def on_data(self, pkt):
        sm = self.sim
        M, N = sm.M, sm.a.window
        if not pkt.ok():
            sm.log("RECEIVER", "RECV DATA corrupted (checksum fail) -> discard, no ACK")
            return
        d = (pkt.seq - self.rcv_base) % M
        if d < N:                                          # inside receive window
            i = self.rcv_base + d
            if i in self.buf:
                sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} duplicate of buffered packet -> re-ACK")
            elif i == self.rcv_base:
                sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} = rcv_base -> accept")
                self.buf[i] = pkt.payload
            else:
                sm.st["buffered"] += 1
                sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} out of order -> BUFFER (rcv_base={self.rcv_base % M})")
                self.buf[i] = pkt.payload
            sm.send_ack(pkt.seq)
            moved = False
            while self.rcv_base in self.buf:
                sm.out.append(self.buf.pop(self.rcv_base))
                sm.log("RECEIVER", f"deliver #{self.rcv_base} to application")
                self.rcv_base += 1
                moved = True
            if moved:
                sm.log("RECEIVER", f"window slides: rcv_base={self.rcv_base % M}({self.rcv_base}) "
                                   f"window=[{self.rcv_base}..{self.rcv_base + N - 1}]")
        elif d >= M - N:                                   # previous window: already delivered
            sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} already delivered (old window) -> re-ACK")
            sm.send_ack(pkt.seq)
        else:
            sm.log("RECEIVER", f"RECV DATA seq={pkt.seq} outside both windows -> ignore")

# Command line
def build_parser():
    p = argparse.ArgumentParser(description="GBN / SR over a simulated unreliable satellite link")
    p.add_argument("--protocol", choices=["gbn", "sr"], required=True)
    p.add_argument("--packets", type=int, default=200, help="number of data packets")
    p.add_argument("--window", type=int, default=4, help="window size N")
    p.add_argument("--seq-bits", type=int, default=3, help="k: sequence numbers are mod 2^k")
    p.add_argument("--loss", type=float, default=0.0, help="loss probability (packets and ACKs)")
    p.add_argument("--corrupt", type=float, default=0.0, help="corruption probability (packets and ACKs)")
    p.add_argument("--delay", type=float, default=0.0, help="extra-delay probability (packets and ACKs)")
    p.add_argument("--delay-min", type=float, default=50.0, help="min extra delay (ms)")
    p.add_argument("--delay-max", type=float, default=300.0, help="max extra delay (ms)")
    p.add_argument("--timeout", type=float, default=600.0, help="retransmission timeout (ms)")
    p.add_argument("--seed", type=int, default=585, help="random seed = last 4 digits of roll number")
    p.add_argument("--rate", type=float, default=2e6, help="link rate R (bits/s)")
    p.add_argument("--rtt", type=float, default=500.0, help="round-trip propagation delay (ms)")
    p.add_argument("--pkt-bytes", type=int, default=1000, help="packet size L (bytes)")
    p.add_argument("--drop-first", type=int, nargs="*", default=[],
                   help="scripted loss: drop the FIRST transmission of these data packet indices")
    p.add_argument("--quiet", action="store_true", help="print only the summary")
    p.add_argument("--log-file", default=None, help="write the full event log to this file")
    p.add_argument("--unsafe", action="store_true", help="allow window sizes that break the sequence-number rule")
    p.add_argument("--max-time", type=float, default=1e8, help="abort after this many ms of virtual time")
    p.add_argument("--max-events", type=int, default=5_000_000)
    p.add_argument("--json", action="store_true", help="print the summary as JSON")
    return p

def run(args):
    M = 2 ** args.seq_bits
    limit = M - 1 if args.protocol == "gbn" else M // 2
    if args.window > limit and not args.unsafe:
        sys.exit(f"error: {args.protocol.upper()} with k={args.seq_bits} (M={M}) needs window <= {limit}; "
                 f"use --unsafe to run it anyway (to demonstrate ambiguity)")
    sim = Sim(args)
    res = sim.run()
    if args.log_file:
        with open(args.log_file, "w") as f:
            f.write("\n".join(sim.lines) + "\n")
    return res

def main():
    args = build_parser().parse_args()
    res = run(args)
    if args.json:
        print(json.dumps(res, indent=2))
    else:
        print("\n===== SUMMARY =====")
        for k, v in res.items():
            print(f"{k:>18}: {v}")

if __name__ == "__main__":
    main()