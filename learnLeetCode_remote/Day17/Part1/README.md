# Day 17 — Part 1: Minimum Cost to Cut a Stick (LC 1547)

Approach:
- Interval DP (top-down with memoization).
- Add 0 and n to `cuts`, sort.
- dp(l, r) = minimal cost to perform all cuts strictly between cuts[l] and cuts[r].
- Try all intermediate cut positions i and compute cost = cuts[r]-cuts[l] + dp(l,i) + dp(i,r).

Files:
- `min_cost_cut.py` (Python top-down with lru_cache)
- `min_cost_cut.cpp` (C++ top-down with memo table)

Try:
```
python min_cost_cut.py
```
