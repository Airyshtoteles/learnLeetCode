# Day 12 — Part 5: Optimization for Large Grids

**Problem**: Find shortest path efficiently on **large grids** (n, m ≤ 500) with all previous mechanics.

## Why Optimization?
Previous parts used BFS with **step-based state space**: `(row, col, usedPortal, steps)`.
- For large grids, this explodes to O(n × m × max_steps) states.
- Part 5 uses **A*** to explore promising paths first, reducing wasted exploration.

## A* Approach
Instead of exploring all states at depth d before d+1, A* uses a **priority queue** with:
- **g(state)** = actual steps taken so far
- **h(state)** = Manhattan distance to end (heuristic)
- **f(state) = g + h** (estimated total cost)

### Manhattan Heuristic
```
h(r, c) = |r - end_r| + |c - end_c|
```
This is **admissible** (never overestimates) because:
- Best case: straight-line path with no obstacles
- Actual path can't be shorter than Manhattan distance

### Algorithm
1. Find start `S`, end `E`, and portals `P`.
2. Initialize priority queue with `(f, g, r, c, usedPortal)`.
3. Pop state with lowest `f` score.
4. If state already visited, skip (avoid duplicate exploration).
5. If at end, return `g` (steps).
6. For each neighbor:
   - Apply dynamic wall check: `blocked_row = (g + 1) // t`
   - Apply portal deactivation: `portals_active = ((g + 1) // t < 3)`
   - Calculate `f = (g + 1) + manhattan(neighbor, end)`
   - Push to priority queue.

## Complexity
- **Time**: O(n × m × log(n × m)) — priority queue operations
- **Space**: O(n × m) — visited states (without step count in state space)

## Key Optimization
Unlike BFS which tracks `(r, c, usedPortal, steps)`, A* tracks `(r, c, usedPortal)`:
- Only one visit per state configuration.
- Priority queue ensures we reach each state with **minimum steps first**.
- This is safe because earlier arrivals always have lower or equal `g` values.

## Example
```
Input:
grid = [
  "S.#.",
  ".P..",
  "..#E",
  "P..."
]
t = 2

A* explores in order of increasing f = g + h:
1. Start (0,0): f = 0 + 4 = 4
2. Right (0,1): f = 1 + 3 = 4
3. Portal (1,1): f = 2 + 2 = 4
...

A* finds optimal path faster than BFS by prioritizing states closer to end.
```

## Files
- `optimized.py` — Python A* implementation
- `optimized.cpp` — C++17 A* implementation

## How to Run

**Python**:
```powershell
python .\Part5\optimized.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part5\optimized.cpp -o .\Part5\optimized.exe ; if ($?) { .\Part5\optimized.exe }
```

## Notes
- A* is **optimal** when heuristic is admissible and consistent.
- Manhattan distance is both admissible and consistent for grid pathfinding.
- For grids where obstacles are sparse, A* can be **orders of magnitude faster** than BFS.
- Part 5 completes Day12 challenge with production-ready efficiency!
