# Day 30 — Part 4: New 21 Game

Problem (LeetCode 837): Alice draws numbers uniformly from 1..maxPts until her score reaches at least k; what is the probability her score is at most n?

Key idea:
- Probability DP with sliding window.
- Let dp[x] be the probability to get total x. Transitions come only from totals < k (game continues). For x ≥ 1:
  - dp[x] = (dp[x-1] + dp[x-2] + ... + dp[x-maxPts]) / maxPts, but only terms where index < k.
- Maintain a moving window sum over the last maxPts values that are < k.
- Initialization: dp[0] = 1, windowSum = 1.
- For x from 1..n: dp[x] = windowSum / maxPts; if x < k add dp[x] to windowSum; if x - maxPts ≥ 0 and x - maxPts < k, subtract dp[x - maxPts] from windowSum.
- The answer is sum(dp[x]) for x in [k..n]. Handle fast-1 cases: if k == 0 or n ≥ k - 1 + maxPts, probability is 1.

Complexity:
- O(n) time, O(n) space.

Files:
- new_21_game.py — Python implementation.
- new_21_game.cpp — C++17 implementation.
