# Max Sum of 3 Non-overlapping Subarrays

Difficulty: Hard

Given an array `nums` and an integer `k`, find three non-overlapping subarrays of length `k` with maximum total sum. Return their starting indices.

## Approach (Precompute k-window sums + Best Left/Right)
- Compute `win[i]` = sum of `nums[i..i+k-1]` for `i in [0..n-k]`.
- `left[i]`: index in `[0..i]` with max `win[idx]` (tie broken by smaller index).
- `right[i]`: index in `[i..n-k]` with max `win[idx]` (tie broken by larger index preference by scanning from right, but we keep earliest index on equal to match common solutions).
- Iterate middle `m` in `[k..n-2k]` and compute `win[left[m-k]] + win[m] + win[right[m+k]]`.

- Time: `O(n)`
- Space: `O(n)`
