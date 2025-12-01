# Day 20 — Part 3: Strictly Increasing Paths in a Grid (LC 2328)

Approach:
- DFS + memo: dp[x][y] = number of increasing paths starting at (x,y).
- Transition to neighbors with greater value, include the single-cell path.
- Sum over all cells, mod 1e9+7.

Complexity:
- Time: O(m*n*4) with memoization.
- Space: O(m*n) for memo and recursion.

Files:
- increasing_paths.py — Python implementation with example.
- increasing_paths.cpp — C++ implementation with example in main().
