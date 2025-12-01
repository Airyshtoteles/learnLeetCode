# Day 24 — Part 2: Ciphered Crime Logs

Task: Given string s and integer k, decode by XORing each character’s ASCII with k, then return the longest palindromic substring of the decoded string.

Approach:
- Decode: t[i] = char(ord(s[i]) XOR k).
- Longest palindromic substring by expand-around-center in O(n^2) worst-case but fast in practice.

Note on example: The provided sample mapping to "level" does not match simple ASCII XOR; this solution implements the general method per the hint.

Files:
- ciphered_crime_logs.py — Python implementation.
- ciphered_crime_logs.cpp — C++17 implementation.
