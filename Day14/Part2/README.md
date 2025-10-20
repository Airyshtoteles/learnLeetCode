# Day 14 — Part 2: BFS with Dynamic Portals

We implement BFS where portal positions remap every `t` steps. To keep it deterministic (no RNG), we simulate remapping by choosing `pcount` cells from the list of traversable cells `(E or P)` starting from an offset equal to the current phase `phase = steps // t`.

- If you step into a portal cell at the current phase, you get teleported instantly to the next portal in the sorted list (no extra step).
- If there are 0 or 1 portals at a phase, teleportation is a no-op.

Python: `bfs_dynamic.py`
C++: `bfs_dynamic.cpp`

State: Basic 2D visited is used here as a baseline. Later parts refine it with `(x,y,steps%t)`.
