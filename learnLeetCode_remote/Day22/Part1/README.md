# Day 22 — Part 1: Strange Printer (LC 664)

Idea:
- Compress consecutive duplicates (doesn’t change optimal turns).
- Interval DP: dp[i][j] = min turns to print s[i..j]. Base dp[i][i]=1.
- Transition: dp[i][j] = dp[i+1][j] + 1, and for any k in (i+1..j] with s[i]==s[k], we can merge the first char’s print with s[k], so
  dp[i][j] = min(dp[i][j], dp[i+1][k-1] + dp[k][j]).

Complexity:
- O(n^3) time, O(n^2) space (n ≤ ~100 typical).

Files:
- strange_printer.py — Python interval DP with memo and compression.
- strange_printer.cpp — C++ bottom-up interval DP with compression.
