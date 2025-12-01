# Day 16 — Part 2: Maximum Value of K Coins From Piles (LC 2218)

DP approach:
- dp[j] = best value using exactly j coins after processing some piles
- For each pile, precompute prefix sums and update dp descending j, trying x coins from this pile.

Files:
- `max_k_coins.py`
- `max_k_coins.cpp`

Try:
```
python max_k_coins.py
```
