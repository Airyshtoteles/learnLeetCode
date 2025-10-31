# Day 25 — Part 1: The Dungeon of Echoes

Assumptions (to make the rules precise):
- You can move 4-directionally into cells that are not walls: cells with value 0 or 2 are passable; 1 is a wall.
- If you stand on a portal (value 2), you may teleport to any other portal; this costs 1 step.
- After each teleport, the echo destroys the source row and the source column: all 0 in that row/column turn into 1 (walls). Portals (2) remain passable.

We then run BFS on the augmented state (r, c, rowMask, colMask), where rowMask and colMask mark which rows/columns were destroyed so far. A move is valid if the next cell is not a wall under the current masks (2 is always allowed).

Complexity: The worst-case state space is O(m·n·2^m·2^n), so this is intended for small grids. It matches the hint via BFS plus treating all portals as a compressed complete teleport graph.

Files:
- dungeon_of_echoes.py — Python BFS implementation.
- dungeon_of_echoes.cpp — C++17 version with a small demo.
