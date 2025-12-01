# Day 19 — Part 2: Minimum Window Subsequence (LC 727)

Approach:
- Two-pointer sweep: pick a start where s[i] == t[0], forward-scan to match all of t; once found end, backward-scan to shrink to the minimal start.
- Repeat by advancing start and take the shortest window seen.

Complexity:
- Worst-case O(n*m) time, O(1) extra space.

Files:
- minimum_window_subsequence.py — Python implementation with example.
- minimum_window_subsequence.cpp — C++ implementation with example in main().
