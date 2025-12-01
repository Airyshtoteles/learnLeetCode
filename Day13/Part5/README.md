# Day 13 — Part 5: Grid Rotation

**Problem**: Apply grid rotation (90° clockwise, `rCount` times) before beam simulation.

## Grid Rotation
- Each rotation: 90° clockwise
- `rCount` = number of rotations to apply
- `rCount % 4` gives effective rotations (4 rotations = back to original)

### Rotation Formula
For 90° clockwise rotation:
```
new_grid[j][n-1-i] = old_grid[i][j]
```
Where:
- `n` = number of rows in old grid
- New grid dimensions: `m × n` (swapped)

## Approach (Rotate Then Simulate)
1. **Rotate grid** `rCount % 4` times (optimize: only 0-3 rotations needed)
2. **Simulate beam** on rotated grid using Part 4 logic (with reflection limit)
3. Return cell count from simulation

### Why Rotation Matters
- Mirrors behave differently when rotated
- Entry point coordinates remain same, but grid layout changes
- `/` and `\` mirrors swap behavior after 180° rotation

## Complexity
- **Rotation**: O(n × m) per rotation, O(4 × n × m) = O(n × m) total
- **Simulation**: O(min(n × m × 4, limit))
- **Total**: O(n × m + limit)

## Example: Rotation Effect
```
Original grid:
  "...",
  "./.",
  "..."

After 1 rotation (90° CW):
  "...",
  ".\\.",
  "..."
  
Notice: '/' becomes '\' after rotation!
Mirror orientation changes affect beam path.
```

## Files
- `grid_rotation.py` — Python implementation
- `grid_rotation.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part5\grid_rotation.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part5\grid_rotation.cpp -o .\Part5\grid_rotation.exe ; if ($?) { .\Part5\grid_rotation.exe }
```

## Notes
- Rotation is applied **before** simulation (not during)
- `rCount % 4` optimization avoids redundant rotations
- Part 6 will handle multiple queries efficiently with caching
- Grid dimensions swap after odd number of rotations
