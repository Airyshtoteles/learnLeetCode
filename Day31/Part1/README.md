# Day 31 — Part 1: Sliding Trap Maze

You are in an m x n maze with cells:
- 'S' start, 'E' exit, '.' empty, '#' wall, 'T' trap.
- You can move 4-directionally.
- If you step on a trap cell 'T', then after you leave that cell, the entire row and column of that trap become permanent walls for the rest of your journey.

Return the minimum steps from 'S' to 'E', or -1 if impossible.

Constraints: 1 ≤ m, n ≤ 10.

Approach:
- BFS on augmented state: (r, c, rowsMask, colsMask), where rowsMask is a bitmask of blocked rows, colsMask for blocked columns.
- When moving into a 'T', we don't block immediately. Only when we step out from that 'T' cell do we apply blocking its row and column.
- To model this cleanly, we treat a move from (r,c, masks) to (nr,nc, newMasks) as:
  - If (r,c) is a trap and we are leaving it, then set the row r and column c in masks before entering (nr,nc).
- Valid next cell requires: not a wall '#', not in a blocked row/col by masks (unless it is the current position before leaving), and within bounds.
- Keep visited set on (r, c, rowsMask, colsMask) to avoid repeats.

Complexity:
- Max masks combinations ≈ 2^m * 2^n with m,n ≤ 10, worst case 2^20; BFS prunes heavily by walls and traps; acceptable for these limits.

Files:
- sliding_trap_maze.py — Python BFS reference.
- sliding_trap_maze.cpp — C++17 BFS implementation.
