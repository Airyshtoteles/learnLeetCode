# Day 32 — Part 5: Flip Matrix to Zero

Binary matrix m x n. One move: choose (i,j) and flip it and its 4-neighbors. Find the minimum number of moves to make all zeros; return -1 if impossible.

Approach:
- Encode board as bitmask of m*n bits. Precompute flip masks for each cell (itself + neighbors).
- BFS from start mask; target = 0.

Files:
- flip_matrix_to_zero.py — Python BFS on bitmask.
- flip_matrix_to_zero.cpp — C++17 BFS on bitmask.
