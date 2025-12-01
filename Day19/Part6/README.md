# Day 19 — Part 6: N-Queens II (LC 52)

Approach:
- Backtracking with bitmasks for columns, main diagonals, and anti-diagonals.
- For each row, compute available positions via bitmask and recurse.

Complexity:
- Time: O(N!) in worst case but pruned heavily via bitmasks.
- Space: O(N) recursion depth.

Files:
- n_queens_ii.py — Python backtracking with bitmasks; example n=4 → 2.
- n_queens_ii.cpp — C++ counterpart with example in main().
