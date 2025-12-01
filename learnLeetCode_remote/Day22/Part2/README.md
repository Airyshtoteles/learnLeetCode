# Day 22 — Part 2: Minimum Number of Operations to Make Array Continuous (LC 2009)

Approach:
- Let n = original length. Remove duplicates and sort: arr.
- Use sliding window on arr to maximize how many can be kept within a range of width n (values in [x, x+n-1]).
- Answer = n - maxKept.

Complexity:
- Time: O(n log n) for sort + O(n) for window.
- Space: O(n) for unique array.

Files:
- make_array_continuous.py — Python two-pointer approach with examples.
- make_array_continuous.cpp — C++ two-pointer approach with examples in main().
