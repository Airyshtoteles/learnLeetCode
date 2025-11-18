# Max Profit with K Non-overlapping Intervals

Difficulty: Hard — DP + Binary Search

Given `n` jobs as intervals `jobs[i] = [start, end, profit]` (non-negative times, `start < end`) and an integer `K`, pick at most `K` non-overlapping intervals to maximize total profit.

Return the maximum profit.

## Approach (Sort + Prev Index + DP)
- Sort jobs by `end`. Precompute `prev[i]`: the last job index `p < i` with `jobs[p].end <= jobs[i].start` using binary search.
- DP: `dp[k][i]` = best profit using first `i` jobs with at most `k` picks.
  - Transition: `dp[k][i] = max( dp[k][i-1], dp[k-1][prev[i]] + profit[i] )` with `dp[*][0] = 0`.
- Space optimize on `k`.

Complexity: `O(n log n + K n)` time, `O(n)` space per layer.
