# Day 21 — Part 4: Minimum Insertion Steps to Make a String Palindrome (LC 1312)

Approach:
- The minimal insertions equals n - LPS(s), and LPS(s) is LCS(s, reverse(s)).
- Compute LCS with O(n^2) time and O(n) space.

Complexity:
- Time: O(n^2)
- Space: O(n)

Files:
- min_insertions_palindrome.py — Python LCS approach with examples.
- min_insertions_palindrome.cpp — C++ LCS approach with examples in main().
