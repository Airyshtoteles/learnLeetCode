# Sliding Window Median (Hard)

Given an integer array `nums` and a window size `k`, return an array of medians for each sliding window of size `k` from left to right. For even `k`, the median is the average of the two middle values.

Example
```
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [1.0,-1.0,-1.0,3.0,5.0,6.0]
```

## Approach
- Maintain two halves of the window:
  - Max-heap `lo` for the lower half, min-heap `hi` for the upper half (Python: lazy deletions).
  - Or in C++, use two balanced multisets: `lo` holds the larger half of smaller elements (max side), `hi` holds the smaller half of larger elements.
- Rebalance to keep sizes within 1 and ensure all elements in `lo` ≤ elements in `hi`.
- Insert the new value, erase the outgoing value, then read median.

- Time: `O(n log k)`
- Space: `O(k)`
