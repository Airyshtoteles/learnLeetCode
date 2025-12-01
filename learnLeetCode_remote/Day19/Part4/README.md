# Day 19 — Part 4: Shortest Path to Get All Keys (LC 864)

Approach:
- BFS in grid with state (x, y, keyMask).
- If cell is a key, set the respective bit; if it's a door, require the bit to be present.
- Stop when keyMask == allKeysMask.

Complexity:
- Time: O(R*C*2^K) with K ≤ 6.
- Space: O(R*C*2^K).

Files:
- shortest_path_all_keys.py — Python BFS with example.
- shortest_path_all_keys.cpp — C++ BFS with example in main().
