# Temporal Labyrinth Pathfinding

Grid m x n with:
- 'S' start, 'E' exit, 'W' wall
- '0'..'9' portals; a portal with digit X can be entered only when `time % X == 0` (assume '0' means always active). Entering a portal teleports you instantly to any other portal with the same digit at no extra time.

You can move in 4 directions, one cell per second, and optionally wait in place.
Return the minimum time to reach 'E', or -1 if impossible.

## Approach
- Precompute positions of each digit.
- Let L = lcm of all portal digits X>0 (upper bound 2520). Track visited by (r, c, t % L).
- BFS over time with moves: up/down/left/right or wait.
  - Move to neighbor at time t+1 if you are in an open cell at time t (non-'W'), and neighbor is not 'W'.
  - If neighbor is a digit X, allow the step only if `(t+1) % X == 0` (or X==0 always true); then teleport to all other same-digit cells at the same time `t+1`.

This guarantees shortest time while handling periodic constraints.

## Files
- `temporal_labyrinth.py` — Python BFS with waiting + portals
- `temporal_labyrinth.cpp` — C++17 BFS
