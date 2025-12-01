# Day 14 — Part 5: Full Integration

Class `Solution` integrates Parts 1–4:
- Parse S, X, portals, and empty/portal cells for potential remaps
- Deterministic portal remap every `t` steps using phase = steps // t
- Teleport instantly on portal cells to the next portal in the list
- BFS with visited[x][y][step%t]

Files:
- Python: `solution.py`
- C++: `solution.cpp`

Example (from prompt) should output `7` for t=3 on the included maze.
