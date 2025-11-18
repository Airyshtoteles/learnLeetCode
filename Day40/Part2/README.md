# Minimum Changes to Split into K Palindromes

Difficulty: Hard — DP on Partitions + Precomputed Palindrome Costs

Given a string `s` and integer `K`, split `s` into exactly `K` non-empty substrings so that the total number of character changes needed to make each substring a palindrome is minimized.

Return that minimum number of changes.

## Approach (Cost Matrix + DP)
- Precompute `cost[i][j]` = minimal changes to make `s[i..j]` a palindrome in `O(n^2)`.
- DP: `dp[k][i]` = minimal changes to split prefix `s[:i]` into `k` palindromes.
  - Transition: `dp[k][i] = min_{t< i} dp[k-1][t] + cost[t][i-1]`.
- Answer: `dp[K][n]`.

Complexity: `O(n^2 + K n^2)` time, `O(n^2)` space.
