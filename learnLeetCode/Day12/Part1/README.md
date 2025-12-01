# Day 12 — Part 1: Dynamic Walls and Magic Portals (Basic BFS)

**Problem**: Find the shortest path from `S` (start) to `E` (end) in a 2D grid.

## Grid Symbols
- `'.'` — Empty passable cell
- `'#'` — Wall (impassable)
- `'S'` — Start position
- `'E'` — End position
- `'P'` — Portal (treated as empty in Part 1)

## Approach (Standard BFS)
1. Find start `S` and end `E` positions.
2. Initialize BFS queue with start position and step count 0.
3. Mark start as visited.
4. For each position, explore 4 neighbors (up, down, left, right).
5. If neighbor is in bounds, not visited, and not a wall:
   - Mark as visited and enqueue with steps + 1.
6. Return steps when `E` is reached, or -1 if unreachable.

## Complexity
- **Time**: O(n × m) — each cell visited at most once
- **Space**: O(n × m) — for visited set and queue

## Example
```
Input:
grid = [
  "S.#.",
  ".P..",
  "..#E",
  "P..."
]

Output: 6 (one possible path length without special mechanics)
```

## Files
- `magic_portals.py` — Python implementation
- `magic_portals.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part1\magic_portals.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part1\magic_portals.cpp -o .\Part1\magic_portals.exe ; if ($?) { .\Part1\magic_portals.exe }
```

## Notes
- Part 1 ignores portal mechanics and dynamic walls.
- Serves as baseline for comparing optimized solutions in later parts.
