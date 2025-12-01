# Day 19 — Part 5: Median of Two Sorted Arrays (LC 4)

Approach:
- Binary search the partition on the smaller array so that left parts contain half of the total elements and max(left) ≤ min(right).
- Compute median based on odd/even total length.

Complexity:
- Time: O(log min(m, n)).
- Space: O(1).

Files:
- median_two_sorted_arrays.py — Python implementation with example.
- median_two_sorted_arrays.cpp — C++ implementation with example in main().
