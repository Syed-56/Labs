# CN Assignment II - Tasks 3 and 4 (Roll No. 24K-0585, seed = 585)

Python 3.8+. The simulator uses only the standard library; `matplotlib` is needed only for the graph.
No ready-made GBN/SR/reliable-transport library is used.

## Files
```
src/rdt_sim.py          Task 3: checksum, unreliable channel, GBN, SR
src/run_experiments.py  Task 4: scenarios A, B, C for both protocols -> table, graph, logs
results/                results_table.md, results.csv, results.json, gbn_vs_sr.png
logs/                   full event log of each Task-4 run (seed 585)
```

## Sample command
```
cd src
python3 rdt_sim.py --protocol sr --packets 200 --window 4 --seq-bits 3 --loss 0.05 --corrupt 0.05 --delay 0.10 --timeout 600 --seed 585
```
Prints a log line for every send, receive, ACK, loss, corruption, delay, timeout and retransmission, then a summary.

## Parameters
| flag | meaning | default |
|---|---|---|
| `--protocol gbn\|sr` | protocol | required |
| `--packets` | number of data packets | 200 |
| `--window` | window size N | 4 |
| `--seq-bits` | k, sequence numbers wrap modulo 2^k | 3 |
| `--loss / --corrupt / --delay` | probability for each packet AND each ACK | 0 |
| `--delay-min / --delay-max` | extra delay range (ms) | 50 / 300 |
| `--timeout` | retransmission timeout (ms) | 600 |
| `--seed` | random seed (last 4 digits of roll number) | 585 |
| `--rate / --rtt / --pkt-bytes` | R (bit/s), RTT (ms), L (bytes) | 2e6 / 500 / 1000 |
| `--drop-first i j ...` | scripted loss of the first copy of those packets | none |
| `--quiet`, `--log-file F`, `--json` | output control | |
| `--unsafe` | allow N above the sequence-number limit | off |

Window limits are enforced: GBN needs N <= 2^k - 1, SR needs N <= 2^(k-1).

## Reproduce Task 4
```
cd src
python3 run_experiments.py --seed 585
```