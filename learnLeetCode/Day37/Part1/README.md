# Minimum Window Substring (LeetCode 76)

Difficulty: Hard

Given strings `s` and `t`, return the minimum window in `s` that contains all the characters of `t`. If there is no such window, return an empty string.

## Approach (Sliding Window)
- Count required frequencies from `t`.
- Expand right pointer, decreasing needs; when all needs satisfied, try to shrink from left to minimize length while keeping valid.
- Track best window positions.

- Time: `O(|s| + |t|)`
- Space: `O(1)` (alphabet bounded by ASCII)
