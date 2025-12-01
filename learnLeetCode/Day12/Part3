# Day 12 — Part 3: Dynamic Walls

**Problem**: Find shortest path with **portals** and **dynamic walls** that appear over time.

## Dynamic Wall Mechanics
- Every `t` steps, row `k` becomes **completely blocked** (all cells become walls).
- `k = current_steps // t`
- Example: if `t=2`, then:
  - At step 2: row 1 blocked
  - At step 4: row 2 blocked
  - At step 6: row 3 blocked

## Approach (Time-Aware BFS)
Extend BFS state to include **current step count**:
- State: `(row, col, usedPortal, steps)`
- Before moving to next position, calculate: `blocked_row = (steps + 1) // t`
- Skip any move that goes to `blocked_row`.

### Algorithm
1. Find start `S`, end `E`, and collect portals `P`.
2. BFS with state `(r, c, usedPortal, steps)`.
3. For each state transition:
   - Calculate `new_steps = steps + 1`
   - Calculate `blocked_row = new_steps // t`
   - **Skip** any neighbor or portal if `row == blocked_row`
4. Return steps when `E` is reached.

## Complexity
- **Time**: O(n × m × n) — worst case, each cell visited with different step counts
- **Space**: O(n × m × n) — visited states include step count

## Example
```
Input:
grid = [
  "S.#.",   // row 0
  ".P..",   // row 1
  "..#E",   // row 2
  "P..."    // row 3
]
t = 2

Timeline:
- Step 0-1: All rows open
- Step 2-3: Row 1 blocked
- Step 4-5: Row 2 blocked (E is here!)
- Step 6+: Row 3 blocked

Need to reach E before step 4, or find alternate route.
```

## Files
- `dynamic_walls.py` — Python implementation
- `dynamic_walls.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part3\dynamic_walls.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part3\dynamic_walls.cpp -o .\Part3\dynamic_walls.exe ; if ($?) { .\Part3\dynamic_walls.exe }
```

## Notes
- BFS explores states in order of increasing steps, naturally handling time progression.
- Dynamic walls create urgency: must reach goal before critical rows are blocked.
- Part 4 will add portal deactivation after 3 rows change.
- Part 5 will optimize for large grids.
