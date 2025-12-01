# Minimum Cost to Make Array Equal (Weighted)

You are given two arrays `nums` and `cost` (same length). In one operation, you can increase or decrease `nums[i]` by 1; the cost of changing `nums[i]` by `d` is `cost[i] * |d|`.
Return the minimum total cost to make all `nums[i]` equal.

Example
```
Input: nums = [1,3,5,2], cost = [2,3,1,14]
Output: 8
```

## Approach (Weighted Median)
Let target value `x` be the final common value. The total cost is `f(x) = sum cost[i] * |nums[i] - x|`, which is convex in `x`. The minimizer is any weighted median of `nums` with weights `cost`.

- Sort pairs `(nums[i], cost[i])` by `nums[i]`.
- Find the smallest value where cumulative weight ≥ total_weight/2.
- Compute `sum cost[i] * |nums[i] - median|`.

- Time: `O(n log n)`
- Space: `O(1)` extra (besides sort)
