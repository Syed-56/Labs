import socket
import struct
import random
import sys


class DNSClient:
    QUERY_TYPE_A = 1
    QUERY_TYPE_CNAME = 5
    QUERY_CLASS_IN = 1
    DNS_PORT = 53
    QUERY_TIMEOUT = 5
    MAX_UDP_SIZE = 512
    MAX_POINTER_JUMPS = 10

    def __init__(self, dnsServerIp):
        self.dnsServerIp = dnsServerIp
        self.transactionId = None

    def encodeDomainName(self, domain):
        encoded = b''
        domain = domain.rstrip('.')

        if not domain:
            raise ValueError("empty domain name")

        for label in domain.split('.'):
            if not label:
                raise ValueError("empty label in domain name")

            raw = label.encode('idna')
            if len(raw) > 63:
                raise ValueError(f"label too long (max 63 bytes): {label}")

            encoded += bytes([len(raw)]) + raw

        encoded += b'\x00'
        return encoded

    def buildDnsQuery(self, domain):
        self.transactionId = random.randint(0, 65535)

        flags = 0x0100
        qdcount = 1
        ancount = 0
        nscount = 0
        arcount = 0

        header = struct.pack('!HHHHHH', self.transactionId, flags,
                             qdcount, ancount, nscount, arcount)

        qname = self.encodeDomainName(domain)
        qtype = self.QUERY_TYPE_A
        qclass = self.QUERY_CLASS_IN
        question = qname + struct.pack('!HH', qtype, qclass)

        return header + question

    def sendQuery(self, domain):
        sock = None
        try:
            query = self.buildDnsQuery(domain)

            sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            sock.settimeout(self.QUERY_TIMEOUT)

            sock.sendto(query, (self.dnsServerIp, self.DNS_PORT))

            response, _ = sock.recvfrom(self.MAX_UDP_SIZE)
            return response

        except ValueError as e:
            print(f"invalid domain name: {e}")
            return None
        except socket.timeout:
            print(f"error: query timeout (no response from {self.dnsServerIp})")
            return None
        except socket.error as e:
            print(f"socket error: {e}")
            return None
        finally:
            if sock is not None:
                sock.close()

    def parseDnsName(self, response, offset):
        labels = []
        nextOffset = None
        jumps = 0

        while True:
            if offset >= len(response):
                raise ValueError("name runs past end of message")

            length = response[offset]

            if (length & 0xC0) == 0xC0:
                if offset + 1 >= len(response):
                    raise ValueError("truncated compression pointer")

                pointer = ((length & 0x3F) << 8) | response[offset + 1]

                if nextOffset is None:
                    nextOffset = offset + 2

                jumps += 1
                if jumps > self.MAX_POINTER_JUMPS:
                    raise ValueError("compression pointer loop")

                offset = pointer
                continue

            if length & 0xC0:
                raise ValueError("unsupported label type")

            offset += 1

            if length == 0:
                break

            if offset + length > len(response):
                raise ValueError("label runs past end of message")

            label = response[offset:offset + length].decode('utf-8', errors='ignore')
            labels.append(label)
            offset += length

        if nextOffset is None:
            nextOffset = offset

        domainName = '.'.join(labels) if labels else '.'
        return domainName, nextOffset

    def parseDnsResponse(self, response):
        if len(response) < 12:
            return {'error': 'response too short'}

        (respTransactionId, flags, qdcount,
         ancount, nscount, arcount) = struct.unpack('!HHHHHH', response[0:12])

        if respTransactionId != self.transactionId:
            return {'error': 'transaction id mismatch'}

        if not (flags & 0x8000):
            return {'error': 'received a query, not a response'}

        truncated = bool(flags & 0x0200)

        rcode = flags & 0x0F

        responseCodes = {
            0: "no error",
            1: "format error",
            2: "server failure",
            3: "name error (nxdomain)",
            4: "not implemented",
            5: "query refused"
        }

        responseStatus = responseCodes.get(rcode, f"unknown ({rcode})")

        answers = []
        try:
            offset = 12
            for _ in range(qdcount):
                _, offset = self.parseDnsName(response, offset)
                offset += 4

            for _ in range(ancount):
                if offset >= len(response):
                    break

                name, offset = self.parseDnsName(response, offset)

                if offset + 10 > len(response):
                    break

                rrtype, rrclass, ttl, rdlength = struct.unpack(
                    '!HHIH', response[offset:offset + 10])
                offset += 10

                if offset + rdlength > len(response):
                    break

                rdataOffset = offset
                offset += rdlength

                if rrtype == self.QUERY_TYPE_A and rdlength == 4:
                    ipAddress = socket.inet_ntoa(response[rdataOffset:offset])
                    answers.append({
                        'name': name,
                        'type': 'A',
                        'ttl': ttl,
                        'ipAddress': ipAddress
                    })
                elif rrtype == self.QUERY_TYPE_CNAME:
                    cname, _ = self.parseDnsName(response, rdataOffset)
                    answers.append({
                        'name': name,
                        'type': 'CNAME',
                        'ttl': ttl,
                        'cname': cname
                    })
        except ValueError as e:
            return {'error': f'malformed response ({e})'}

        return {
            'transactionId': respTransactionId,
            'responseCode': responseStatus,
            'rcode': rcode,
            'ancount': ancount,
            'truncated': truncated,
            'answers': answers
        }

    def query(self, domain):
        print(f"\nQuerying {domain}...")
        print(f"  (using {self.dnsServerIp}:{self.DNS_PORT})")

        response = self.sendQuery(domain)
        if response is None:
            return None

        return self.parseDnsResponse(response)

    def displayResult(self, domain, result):
        if result is None:
            print("no response received\n")
            return

        if 'error' in result:
            print(f"error: {result['error']}\n")
            return

        print("\nResponse:")
        print(f"  Transaction ID: 0x{result['transactionId']:04X}")
        print(f"  Query: {domain}")
        print("  Query Type: A")
        print(f"  Status: {result['responseCode']}")

        if result['truncated']:
            print("  Warning: response was truncated (TC bit set)")

        if result['rcode'] == 0:
            if result['answers']:
                print(f"  Answer records: {len(result['answers'])}")
                for answer in result['answers']:
                    if answer['type'] == 'A':
                        print(f"    - {answer['name']}  A  {answer['ipAddress']}")
                    else:
                        print(f"    - {answer['name']}  CNAME  {answer['cname']}")
                    print(f"      TTL: {answer['ttl']} seconds")
            else:
                print("  No answer records found")
        else:
            print(f"  Query failed (error code: {result['rcode']})")

        print()


def main():
    print(" Section A")

    while True:
        dnsServer = input("Enter DNS Server IP: ").strip()
        try:
            socket.inet_aton(dnsServer)
            break
        except OSError:
            print("Please enter a valid IPv4 address.\n")

    print(f"\nUsing DNS Server: {dnsServer}")
    print("Enter 'quit' to exit...\n")

    client = DNSClient(dnsServer)

    while True:
        domain = input("Enter domain name to query: ").strip()

        if domain.lower() == 'quit':
            break

        if not domain:
            print("Please enter a valid domain name.\n")
            continue

        result = client.query(domain)
        client.displayResult(domain, result)


if __name__ == '__main__':
    try:
        main()
    except (KeyboardInterrupt, EOFError):
        print("\nProgram Ended!")
        sys.exit(0)