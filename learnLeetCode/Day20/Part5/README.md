# Day 20 — Part 5: Maximum Deletions on a String (LC 2430)

Operation: repeatedly delete a non-empty prefix s[0..k-1] if it equals the next substring s[k..2k-1]. Maximize number of deletions.

Approach:
- Let dp[i] be the max deletions on s[i:]. For each i, consider k from 1..(n-i)/2; if LCP(s[i:], s[i+k:]) >= k, then we can delete the first k and get 1 + dp[i+k]. Take maximum.
- Compute LCP for all offsets k using Z-function on t = s[i:] so that LCP(s[i:], s[i+k:]) = Z[k]. This yields O(n^2) total.

Complexity:
- Time: O(n^2) (Z per suffix + dp).
- Space: O(n).

Files:
- max_deletions_string.py — Python DP + Z with example.
- max_deletions_string.cpp — C++ counterpart with example in main().
