# Burst Balloons (LeetCode 312)

Difficulty: Hard

Given `nums`, you may burst balloons in any order. Bursting `i` yields `nums[i-1]*nums[i]*nums[i+1]` with neighbors shrinking after removal. Return max coins.

## Approach (Interval DP)
Pad array as `val = [1] + nums + [1]`. Let `dp[l][r]` be the max coins by bursting balloons strictly between `(l, r)` (exclusive). For each interval length, try last balloon `k` inside `(l, r)`:

```
dp[l][r] = max over k in (l,r): dp[l][k] + val[l]*val[k]*val[r] + dp[k][r]
```

- Time: `O(n^3)`
- Space: `O(n^2)`
