# K-th Smallest Pair Distance

Difficulty: Hard

Given an integer array `nums` and an integer `k`, return the `k`-th smallest absolute difference between any two elements.

## Approach (Binary Search + Two Pointers)
Sort `nums`. Binary search distance `d` in `[0, max(nums)-min(nums)]`.
For a candidate `d`, count pairs with distance `<= d` using sliding window: for each `i`, advance `j` as far as `nums[j] - nums[i] <= d`; add `j - i - 1`.
If count `>= k`, shrink high; else increase low. Return the smallest `d` with count `>= k`.

- Time: `O(n log W)` where `W` is value range
- Space: `O(1)` extra
