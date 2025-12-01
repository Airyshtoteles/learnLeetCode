# Day 32 — Part 4: Key-Lock Dungeon

Collect all keys 'a'..'f' on an m x n grid with walls '#', start '@', doors 'A'..'F'. A door requires its lowercase key. Find minimum steps to collect all keys.

Approach:
- Count total keys to know target mask (e.g., for k keys, target mask = (1<<k)-1 with key indexing by letter).
- BFS state: (r,c,keyMask). Transitions to 4 neighbors if not wall and if door we have key.
- Use visited[r][c][keyMask]. When key cell, add bit.

Files:
- key_lock_dungeon.py — Python BFS.
- key_lock_dungeon.cpp — C++17 BFS.
