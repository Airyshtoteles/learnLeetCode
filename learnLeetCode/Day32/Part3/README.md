# Day 32 — Part 3: Puzzle Board Restoration (8-Puzzle)

Given a 3x3 board with numbers 1..8 and a blank 0, find the minimum moves to reach the target [[1,2,3],[4,5,6],[7,8,0]], or -1 if impossible.

Approach:
- Check solvability via inversion parity (odd inversions => unsolvable for 3x3 with blank anywhere; actually: solvable iff inversion count is even for 3x3).
- Use A* search with Manhattan distance heuristic: h = sum of |dx|+|dy| of each tile to its goal position.
- State encoded as string "123405678"; neighbors by sliding 0 in 4 directions.

Files:
- puzzle_board_restoration.py — Python A* implementation.
- puzzle_board_restoration.cpp — C++17 A* implementation.
