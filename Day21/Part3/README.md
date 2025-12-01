# Day 21 — Part 3: Palindrome Partitioning IV (LC 1745)

Approach:
- Precompute pal[i][j] = True iff s[i..j] is palindrome in O(n^2).
- Try all splits i<j with pal[0][i] and pal[i+1][j] and pal[j+1][n-1].

Complexity:
- Time: O(n^2)
- Space: O(n^2)

Files:
- pal_partition_iv.py — Python implementation with example.
- pal_partition_iv.cpp — C++ implementation with example in main().
