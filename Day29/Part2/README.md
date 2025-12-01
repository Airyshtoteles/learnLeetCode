# Grid Survival: Monster Path

An m x n grid with k monster positions and a player start. Each second, the player moves to N/S/E/W and monsters also move one step toward the player (reducing Manhattan distance). Find the maximum time the player can survive before any monster reaches the player's position. If a monster is already on the start, return -1.

## Observation
Let `Tm(x,y)` be the earliest time a monster can reach cell (x,y). With 4-neighbor moves and no obstacles, `Tm` is just the grid distance from the closest monster, i.e., multi-source BFS distance.
Let `Tp(x,y)` be the earliest time the player can reach (x,y) from start.
A position (x,y) is safe to occupy at time `t=Tp(x,y)` iff `Tp(x,y) < Tm(x,y)`. The maximum survival time is thus `max Tp(x,y)` over all reachable cells with `Tp(x,y) < Tm(x,y)`.

## Files
- `monster_survival.py` — Python implementation
- `monster_survival.cpp` — C++17 implementation
