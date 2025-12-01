# Day 12 — Part 2: Portal Teleportation

**Problem**: Find shortest path with **one-time portal teleportation**.

## Portal Mechanics
- `'P'` cells are portals.
- When standing on a portal, you can **teleport** to any other portal with **cost 1** (instant).
- You can only use portal teleportation **once** during the entire journey.

## Approach (BFS with Extended State)
Use BFS with state `(row, col, usedPortal)`:
- `usedPortal = False`: haven't used portal yet
- `usedPortal = True`: already used portal (no more teleportation)

### Algorithm
1. Find start `S`, end `E`, and collect all portal positions `P`.
2. Initialize BFS with state `(start_row, start_col, False, 0)`.
3. For each state:
   - **Normal movement**: explore 4 neighbors, keep same `usedPortal` state.
   - **Portal teleportation**: if currently on `P` and `usedPortal = False`:
     - Add all other portals with state `usedPortal = True`.
4. Return steps when `E` is reached.

## Complexity
- **Time**: O(n × m × 2) — each cell visited at most twice (with/without portal)
- **Space**: O(n × m × 2) — visited states

## Example
```
Input:
grid = [
  "S.#.",
  ".P..",
  "..#E",
  "P..."
]

Without portal: 5 steps
With portal: 4 steps (teleport from P at (1,1) to P at (3,0))
```

## Files
- `portal_bfs.py` — Python implementation
- `portal_bfs.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part2\portal_bfs.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part2\portal_bfs.cpp -o .\Part2\portal_bfs.exe ; if ($?) { .\Part2\portal_bfs.exe }
```

## Notes
- Portal teleportation costs 1 step (same as normal movement).
- Using portal early vs. late can produce same or different results depending on grid layout.
- Part 3 will add dynamic walls that change over time.
