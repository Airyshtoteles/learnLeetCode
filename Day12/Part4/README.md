# Day 12 — Part 4: Portal Deactivation

**Problem**: Find shortest path with **dynamic walls** and **portals that deactivate** after 3 row changes.

## Portal Deactivation Rule
- After `steps // t >= 3` (i.e., 3 or more rows have been blocked), **all portals stop working**.
- Any 'P' cell becomes **impassable** (treated as wall `#`).
- This adds strategic pressure: must use portals **early** or find alternate routes.

## Approach (Extended Time-Aware BFS)
Extend Part3 BFS with portal availability check:
- State: `(row, col, usedPortal, steps)`
- Calculate: `portals_active = (steps // t < 3)`
- When moving:
  - Skip any cell with `grid[r][c] == 'P'` if `portals_active == False`
- When considering portal teleportation:
  - Only allow if `portals_active == True`

### Algorithm
1. Find start `S`, end `E`, and collect portals `P`.
2. BFS with state `(r, c, usedPortal, steps)`.
3. For each state:
   - Calculate `new_steps = steps + 1`
   - Calculate `blocked_row = new_steps // t`
   - Calculate `portals_active = (new_steps // t < 3)`
4. Normal movement:
   - Skip if `row == blocked_row`
   - Skip if `cell == 'P'` and `not portals_active`
5. Portal teleportation:
   - Only allow if `on portal` and `not used_portal` and `portals_active`
6. Return steps when `E` is reached.

## Complexity
- **Time**: O(n × m × n) — each cell visited with different step counts
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
- Step 0-1: All rows open, portals active
- Step 2-3: Row 1 blocked, portals active (1 row changed)
- Step 4-5: Row 2 blocked, portals active (2 rows changed)
- Step 6+: Row 3 blocked, PORTALS DEACTIVATE (3 rows changed)

Strategy: Use portal early (before step 6) or find path without portals.
```

## Files
- `portal_deactivation.py` — Python implementation
- `portal_deactivation.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part4\portal_deactivation.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part4\portal_deactivation.cpp -o .\Part4\portal_deactivation.exe ; if ($?) { .\Part4\portal_deactivation.exe }
```

## Notes
- Portal deactivation creates **time pressure**: must leverage portals in early steps.
- Combines dynamic walls (Part3) with portal constraints (Part2).
- Part 5 will add large-grid optimization (A* or state compression).
