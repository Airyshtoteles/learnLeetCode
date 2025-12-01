# Day 11 — Part 1: Dimensional Labyrinth (3D BFS Basic)

**Problem**: Navigate a 3D labyrinth from `(0,0,0)` to `(n-1,m-1,h-1)` with minimum steps.

## Grid Values
- `0` = empty cell (passable)
- `1` = wall (impassable)
- `2` = portal (treated as empty in Part 1)

## Movement
You can move in 6 directions:
- `(+1, 0, 0)` / `(-1, 0, 0)` — along X-axis
- `(0, +1, 0)` / `(0, -1, 0)` — along Y-axis
- `(0, 0, +1)` / `(0, 0, -1)` — along Z-axis

Each step costs 1.

## Approach (Standard BFS)
1. Initialize queue with starting position `(0,0,0)` and cost 0.
2. Mark starting position as visited.
3. For each position, explore all 6 neighbors.
4. If neighbor is within bounds, not a wall, and not visited:
   - Mark as visited and enqueue with cost + 1.
5. Return cost when destination is reached, or -1 if queue empties.

## Complexity
- **Time**: O(n × m × h) — each cell visited at most once
- **Space**: O(n × m × h) — for visited set and queue

## Files
- `labyrinth_3d.py` — Python implementation with BFS
- `labyrinth_3d.cpp` — C++17 implementation with BFS

## How to Run

**Python**:
```powershell
python .\Part1\labyrinth_3d.py
```

**C++** (MinGW g++):
```powershell
g++ -std=c++17 -O2 .\Part1\labyrinth_3d.cpp -o .\Part1\labyrinth_3d.exe ; if ($?) { .\Part1\labyrinth_3d.exe }
```

## Notes
- This Part 1 ignores portal mechanics (treats `2` as empty).
- Part 2 will add teleportation via portals.
- Part 3 will optimize with A* heuristic.
