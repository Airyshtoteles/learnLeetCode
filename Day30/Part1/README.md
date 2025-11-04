# Day 30 — Part 1: Stone Game V

Problem: Given an array stoneValue, you split a subarray into two non-empty parts. You gain the sum of the part with smaller total. Then you continue recursively on the chosen part (the one with the smaller sum; if equal, you can choose either part). Maximize the total score.

Key idea:
- Interval DP with prefix sums.
- Let dp[l][r] be the maximum score attainable from subarray [l..r]. For any split k in [l..r-1], compare left = sum(l..k) and right = sum(k+1..r):
  - If left < right, we must take left and continue on [l..k]: candidate = left + dp[l][k].
  - If left > right, we must take right and continue on [k+1..r]: candidate = right + dp[k+1][r].
  - If left == right, we may choose either: candidate = left + max(dp[l][k], dp[k+1][r]).
- Take the maximum candidate over all k.

Complexity:
- O(n^3) time, O(n^2) space. This is the classic, clear solution for learning; can be optimized to O(n^2) with additional techniques when needed.

Files:
- stone_game_v.py — Python implementation with memoization.
- stone_game_v.cpp — C++17 implementation.
