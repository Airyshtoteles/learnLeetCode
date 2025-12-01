# Palindrome Partitioning II (Minimum Cuts)

Difficulty: Hard

Given a string `s`, partition `s` such that every substring is a palindrome. Return the minimum cuts needed for a palindrome partitioning of `s`.

## Approach (Center Expansion DP)
Maintain `cut[i]` = min cuts for prefix `s[:i]`. Initialize `cut[0] = -1` (no cut before first char). For each center (odd and even), expand and update `cut[r+1] = min(cut[r+1], 1 + cut[l])` whenever `s[l..r]` is palindrome.

- Time: `O(n^2)` worst-case
- Space: `O(n)`
