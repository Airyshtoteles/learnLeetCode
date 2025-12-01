# Dungeon Tokens

An n x n grid with positive/negative tokens. Start at (0,0), move only right or down to (n-1,n-1). Collect sum along the path, but the running total must never become negative at any step. Maximize the final total; return -1 if impossible.

## Approach (DP with feasibility)
- Let `dp[i][j]` be the maximum total upon reaching (i,j) without ever going negative before or at (i,j). Initialize as -inf.
- Transition from top or left: if `dp[p]` is valid and `dp[p] + grid[i][j] >= 0`, then `dp[i][j] = max(dp[i][j], dp[p] + grid[i][j])`.
- Start cell must satisfy `grid[0][0] >= 0`.
- Answer is `dp[n-1][n-1]` if valid, else -1.

## Files
- `dungeon_tokens.py` — Python DP
- `dungeon_tokens.cpp` — C++17 DP
