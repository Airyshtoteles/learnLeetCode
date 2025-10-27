# Day 21 — Part 2: Shortest Path Visiting All Nodes (LC 847)

Approach:
- BFS on state (node, visitedMask) starting from all nodes simultaneously.
- When visitedMask == (1<<n)-1, return current distance.

Complexity:
- Time: O(n * 2^n)
- Space: O(n * 2^n)

Files:
- shortest_path_visiting_all_nodes.py — Python BFS with example.
- shortest_path_visiting_all_nodes.cpp — C++ BFS with example in main().
