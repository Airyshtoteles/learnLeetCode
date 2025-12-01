# Shortest Subarray with Sum ≥ K

Difficulty: Hard

Given an integer array `nums` and an integer `K`, return the length of the shortest non-empty subarray with sum at least `K`. If there isn't one, return `-1`.

## Approach (Monotonic Deque on Prefix Sums)
Let prefix `P[i] = sum(nums[:i])`. For each `i`, we want the smallest `j < i` such that `P[i]-P[j] >= K` and `j` is as large as possible. Maintain a deque of candidate indices with increasing `P[j]`. For each `i`:
- While deque not empty and `P[i]-P[deque[0]] >= K`, update answer and pop left.
- While deque not empty and `P[i] <= P[deque[-1]]`, pop right.
- Push `i`.

- Time: `O(n)`
- Space: `O(n)`
