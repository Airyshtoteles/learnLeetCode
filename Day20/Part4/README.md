# Day 20 — Part 4: Reverse Odd Levels of Binary Tree (LC 2415)

Approach:
- BFS level order; when on odd level, reverse the values across the layer (swap symmetric nodes).
- Structure is perfect tree, so sizes align naturally.

Complexity:
- Time: O(n)
- Space: O(n)

Files:
- reverse_odd_levels.py — Python BFS with example.
- reverse_odd_levels.cpp — C++ BFS with example in main().
