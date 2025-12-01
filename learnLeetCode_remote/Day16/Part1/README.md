# Day 16 — Part 1: Minimum Cost to Split Array (LC 2547)

We use DP over prefixes:
- dp[i] = min cost to split nums[:i]
- dp[0] = 0
- For each i, scan j from i-1..0, track duplicate cost for subarray nums[j:i].

Duplicate counting:
- For value with frequency f in the subarray, it contributes f if f >= 2 (else 0).
- Incrementally: when a count hits 2 add +2; for >2 add +1.

This reference is O(n^2) for clarity.

Files:
- `min_cost_split.py`
- `min_cost_split.cpp`

Try:
```
python min_cost_split.py
```
