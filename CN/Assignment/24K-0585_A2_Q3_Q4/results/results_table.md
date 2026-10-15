Seed = 585, 200 packets, N = 4, k = 3, timeout = 600 ms, R = 2 Mbps, RTT = 500 ms, L = 1000 B

| Scenario | Protocol | Transmitted | Retransmissions | Delivered | Time (s) | Throughput (kbps) | Timeouts |
|---|---|---|---|---|---|---|---|
| A: Reliable | GBN | 200 | 0 | 200/200 | 25.21 | 63.5 | 0 |
| A: Reliable | SR | 200 | 0 | 200/200 | 25.21 | 63.5 | 0 |
| B: Loss 0.10 | GBN | 314 | 114 | 200/200 | 48.82 | 32.8 | 29 |
| B: Loss 0.10 | SR | 255 | 55 | 200/200 | 41.38 | 38.7 | 55 |
| C: Mixed errors | GBN | 320 | 120 | 200/200 | 47.23 | 33.9 | 30 |
| C: Mixed errors | SR | 305 | 105 | 200/200 | 41.91 | 38.2 | 105 |

Mean over seeds 0..29 (extra robustness check):

| Scenario | GBN retx | SR retx | GBN time (s) | SR time (s) | all runs correct |
|---|---|---|---|---|---|
| A: Reliable | 0.0 | 0.0 | 25.21 | 25.21 | True |
| B: Loss 0.10 | 87.6 | 46.5 | 44.06 | 41.76 | True |
| C: Mixed errors | 110.5 | 103.1 | 46.23 | 44.36 | True |
