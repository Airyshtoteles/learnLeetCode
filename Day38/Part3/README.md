# Minimum Adjacent Swaps to Group K Ones in Circular Array (Hard)

Given a binary array `nums` arranged in a circle and an integer `k`, return the minimum number of adjacent swaps to make at least one block of `k` ones contiguous.

Example
```
Input: nums = [1,0,1,0,1], k = 2
Output: 0  (already can choose the two adjacent ones across wrap)
```

## Approach (Adjusted Positions + Prefix Sums on Duplicated Indices)
- Gather indices of ones: `pos`.
- Duplicate indices with `+n` to represent wrap: `pos2 = pos + [x+n for x in pos]`.
- For a window of size `k`, consider adjusted positions `adj[i] = pos2[i] - i` to remove spacing effect.
- The minimum swaps for that window equals sum of distances to the median of `adj`.
- Use prefix sums over `adj` to query sums in `O(1)` per window.
- Slide over all `k`-windows within `pos2` but only those starting in `[0, m-1]` (m = number of ones).

- Time: `O(m)` after preprocessing
- Space: `O(m)`
