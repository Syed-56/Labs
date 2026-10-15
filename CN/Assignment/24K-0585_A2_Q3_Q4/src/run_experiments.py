#Task 4
import argparse
import csv
import json
import os
import statistics
import matplotlib
matplotlib.use("Agg")
import matplotlib.pyplot as plt
from rdt_sim import build_parser, run

SCENARIOS = {
    "A: Reliable":      dict(loss=0.0,  corrupt=0.0,  delay=0.0),
    "B: Loss 0.10":     dict(loss=0.10, corrupt=0.0,  delay=0.0),
    "C: Mixed errors":  dict(loss=0.05, corrupt=0.05, delay=0.10),
}

def one(proto, sc, seed, logfile=None):
    args = build_parser().parse_args(
        ["--protocol", proto, "--packets", "200", "--window", "4", "--seq-bits", "3",
         "--seed", str(seed), "--quiet"]
    )
    for k, v in SCENARIOS[sc].items():
        setattr(args, k, v)
    args.log_file = logfile
    return run(args)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--seed", type=int, default=585, help="last 4 digits of roll number")
    ap.add_argument("--outdir", default=os.path.join(os.path.dirname(__file__), ".."))
    ap.add_argument("--avg-seeds", type=int, default=30, help="extra: average over this many seeds")
    o = ap.parse_args()
    res_dir, log_dir = os.path.join(o.outdir, "results"), os.path.join(o.outdir, "logs")
    os.makedirs(res_dir, exist_ok=True)
    os.makedirs(log_dir, exist_ok=True)

    rows = []
    for sc in SCENARIOS:
        for proto in ("gbn", "sr"):
            tag = sc.split(":")[0]
            r = one(proto, sc, o.seed, os.path.join(log_dir, f"{tag}_{proto}_seed{o.seed}.log"))
            r["scenario"] = sc
            rows.append(r)

    # csv 
    cols = ["scenario", "protocol", "transmitted", "retransmissions", "delivered", "time_ms",
            "throughput_kbps", "utilization", "timeouts", "in_order_correct"]
    with open(os.path.join(res_dir, "results.csv"), "w", newline="") as f:
        w = csv.DictWriter(f, fieldnames=cols, extrasaction="ignore")
        w.writeheader()
        w.writerows(rows)

    # markdown table 
    md = [f"Seed = {o.seed}, 200 packets, N = 4, k = 3, timeout = 600 ms, R = 2 Mbps, RTT = 500 ms, L = 1000 B", "",
          "| Scenario | Protocol | Transmitted | Retransmissions | Delivered | Time (s) | Throughput (kbps) | Timeouts |",
          "|---|---|---|---|---|---|---|---|"]
    for r in rows:
        md.append(f"| {r['scenario']} | {r['protocol']} | {r['transmitted']} | {r['retransmissions']} | "
                  f"{r['delivered']}/200 | {r['time_ms']/1000:.2f} | {r['throughput_kbps']:.1f} | {r['timeouts']} |")

    # extra: mean over many seeds
    avg = {}
    for sc in SCENARIOS:
        for proto in ("gbn", "sr"):
            rs = [one(proto, sc, s) for s in range(o.avg_seeds)]
            avg[(sc, proto)] = dict(
                retx=statistics.mean(x["retransmissions"] for x in rs),
                time=statistics.mean(x["time_ms"] for x in rs) / 1000,
                ok=all(x["in_order_correct"] for x in rs))
    md += ["", f"Mean over seeds 0..{o.avg_seeds - 1} (extra robustness check):", "",
           "| Scenario | GBN retx | SR retx | GBN time (s) | SR time (s) | all runs correct |",
           "|---|---|---|---|---|---|"]
    for sc in SCENARIOS:
        g, s = avg[(sc, "gbn")], avg[(sc, "sr")]
        md.append(f"| {sc} | {g['retx']:.1f} | {s['retx']:.1f} | {g['time']:.2f} | {s['time']:.2f} | {g['ok'] and s['ok']} |")
    with open(os.path.join(res_dir, "results_table.md"), "w") as f:
        f.write("\n".join(md) + "\n")
    with open(os.path.join(res_dir, "results.json"), "w") as f:
        json.dump(dict(rows=rows, avg={f"{k[0]}|{k[1]}": v for k, v in avg.items()}), f, indent=1)

    # graph 
    names = list(SCENARIOS)
    short = [n.replace(": ", ":\n") for n in names]
    get = lambda proto, key: [next(r[key] for r in rows if r["scenario"] == n and r["protocol"] == proto) for n in names]
    fig, ax = plt.subplots(1, 3, figsize=(11, 3.4))
    x = range(len(names))
    for a_, key, title, ylab in [
        (ax[0], "retransmissions", "Retransmissions", "packets"),
        (ax[1], "time_ms", "Execution time", "seconds"),
        (ax[2], "throughput_kbps", "Throughput", "kbps"),
    ]:
        g, s = get("GBN", key), get("SR", key)
        if key == "time_ms":
            g, s = [v / 1000 for v in g], [v / 1000 for v in s]
        b1 = a_.bar([i - 0.2 for i in x], g, 0.4, label="GBN", color="#d9822b")
        b2 = a_.bar([i + 0.2 for i in x], s, 0.4, label="SR", color="#2b7bd9")
        for b in list(b1) + list(b2):
            a_.text(b.get_x() + b.get_width() / 2, b.get_height(), f"{b.get_height():.0f}" if key != "time_ms" else f"{b.get_height():.1f}",
                    ha="center", va="bottom", fontsize=8)
        a_.set_xticks(list(x))
        a_.set_xticklabels(short, fontsize=8)
        a_.set_title(title, fontsize=10)
        a_.set_ylabel(ylab, fontsize=9)
        a_.legend(fontsize=8)
    fig.suptitle(f"GBN vs SR (200 packets, N=4, k=3, seed={o.seed})", fontsize=11)
    fig.tight_layout()
    fig.savefig(os.path.join(res_dir, "gbn_vs_sr.png"), dpi=200)
    print("\n".join(md))

if __name__ == "__main__":
    main()