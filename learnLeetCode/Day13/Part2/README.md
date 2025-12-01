# Day 13 — Part 2: Multiple Entry Points

**Problem**: Simulate multiple light beams from different entry points and count **total unique cells** visited by at least one beam.

## Extension from Part 1
- Part 1: Single beam, count cells visited
- Part 2: **k beams**, count **union** of all visited cells

## Approach (Multiple Simulations with Shared Set)
1. Create a **global visited set** to track all cells across all beams
2. For each entry point `(r, c, dir)`:
   - Run beam simulation (same as Part 1)
   - Add visited cells to global set
3. Return size of global visited set

### Why This Works
- Each beam independently explores the grid
- Some cells may be visited by multiple beams (overlaps)
- Using a **set** ensures we count each cell only once
- Time complexity scales with number of entry points

## Complexity
- **Time**: O(k × n × m × 4) — k beams, each visits up to O(n×m×4) states
- **Space**: O(n × m × 4) — global visited set + per-beam state tracking

## Example
```
Input:
grid = [
  ".....",
  "../..",
  "....."
]
entries = [
  (1, 0, 0),  // Beam 1: row 1, col 0, right
  (0, 0, 1)   // Beam 2: row 0, col 0, down
]

Beam 1 path:
- (1,0) → (1,1) → hits '/' → goes up → (0,1) → out
- Cells: {(1,0), (1,1), (0,1)}

Beam 2 path:
- (0,0) → (1,0) → (2,0) → out
- Cells: {(0,0), (1,0), (2,0)}

Union: {(0,0), (0,1), (1,0), (1,1), (2,0)} = 5 cells
```

## Files
- `multi_beam.py` — Python implementation
- `multi_beam.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part2\multi_beam.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part2\multi_beam.cpp -o .\Part2\multi_beam.exe ; if ($?) { .\Part2\multi_beam.exe }
```

## Notes
- Global visited set automatically handles overlaps between beams
- Each beam simulation is independent (no interference)
- Part 3 will add explicit loop detection with `-1` return
- Part 4 will add reflection limit constraints
