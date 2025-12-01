# Day 32 — Part 1: Sliding Portal Puzzle

Grid n x n with cells: '.', '#', 'S', 'T', 'A'-'Z' portals (each letter appears exactly twice). Move in 4 directions into empty or portal cells. Stepping onto a portal teleports you instantly to its paired cell (counts as 1 move total for entering + teleport). Find minimum moves from S to T.

Approach:
- Preprocess portal positions into map letter -> pair (r1,c1),(r2,c2).
- BFS from S; when expanding a portal cell, the neighbor is its paired coordinate.
- Walls '#' blocked; visited set on (r,c) prevents cycles.

Complexity: O(n^2) states.

Files:
- sliding_portal_puzzle.py — Python BFS.
- sliding_portal_puzzle.cpp — C++17 BFS.
