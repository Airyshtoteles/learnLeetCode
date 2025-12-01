# Day 18 — Part 3: Minimum Window Substring (LC 76)

Sliding window with character counts:
- Expand right to include characters and reduce the missing count.
- When all required chars are covered (missing == 0), try to shrink from the left to minimize window.

Complexity:
- Time: O(n), each char visited at most twice.
- Space: O(1) (fixed alphabet) or O(U) for unicode.

Files:
- min_window_substring.py — Python implementation with example.
- min_window_substring.cpp — C++ implementation with example in main().
