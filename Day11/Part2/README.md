# Day 11 — Part 2: Portal Optimization

**Problem**: Navigate a 3D labyrinth with **portal teleportation**.

## Portal Mechanics
- Cells with value `2` are portals.
- When standing on a portal, you can **teleport** to any other portal with cost `k`.
- Normal movement (6 directions) still costs 1 per step.

## Input
- `n, m, h` — grid dimensions
- `k` — portal teleportation cost
- `grid[h][n][m]` — 3D array

## Approach (BFS with Portal Expansion)
1. **Collect all portal positions** during initialization.
2. **Standard BFS** with 6-direction movement (cost 1).
3. **When at a portal**: add all other portals to the queue with cost + k.
4. Use a **visited set** to avoid cycles.

### Optimization
- Only expand portal teleportation when **currently at a portal** (lazy expansion).
- This prevents adding O(P²) edges upfront where P = number of portals.

## Complexity
- **Time**: O(n × m × h + P²) where P = number of portals
  - Each cell visited once: O(n×m×h)
  - Portal expansion: up to O(P) portals × O(P) destinations = O(P²)
- **Space**: O(n × m × h) for visited set and queue

## Files
- `labyrinth_portal.py` — Python implementation with portal BFS
- `labyrinth_portal.cpp` — C++17 implementation with portal BFS

## How to Run

**Python**:
```powershell
python .\Part2\labyrinth_portal.py
```

**C++** (MinGW g++):
```powershell
g++ -std=c++17 -O2 .\Part2\labyrinth_portal.cpp -o .\Part2\labyrinth_portal.exe ; if ($?) { .\Part2\labyrinth_portal.exe }
```

## Example
```
n=3, m=3, h=2, k=2
Portal at (0,2,0) and (1,1,1)
Expected output: ~6
```

## Notes
- Portal teleportation is only beneficial when `k` < distance via normal movement.
- BFS guarantees shortest path in unweighted graphs; here we simulate weighted edges via cost tracking.
