# Day 13 — Part 4: Reflection Limit

**Problem**: Add maximum **reflection limit** to prevent excessive computation. Beam stops after exceeding limit reflections.

## Why Reflection Limit?
- In Part 3, loop detection prevents infinite loops
- But some grids with many mirrors can take O(n×m×4) steps even without loops
- Part 4 adds **computational budget**: max reflections allowed (typically ≤ 10⁴)
- This ensures termination in practical time

## Approach (Reflection Counting)
1. Track **reflection count** (starts at 0)
2. At each step:
   - If on mirror (`/` or `\`), increment reflection count
   - If reflection_count > limit, **stop immediately**
   - Return current cell count
3. Otherwise, continue simulation as before (loop detection still active)

### Key Changes from Part 3
- Add `reflection_count` variable
- Increment when beam hits mirror
- Check `if reflection_count > limit` after each reflection
- Stop early if limit exceeded (prevents runaway computation)

## Complexity
- **Time**: O(min(n × m × 4, limit)) — bounded by both grid size and limit
- **Space**: O(n × m × 4) — visited states set

## Example: Loop with Limit
```
Input:
grid = [
  "/.\\",
  ".#.",
  "\\./",
]
entry = (0, 0, 0)  // top-left, right
limit = 10

Simulation:
- Beam enters loop (would be infinite in Part 3)
- But after 10 reflections, stops automatically
- Returns cells visited within those 10 reflections

This prevents indefinite computation!
```

## Example: Low Limit
```
Input:
grid = [
  "///",
  "///"
]
entry = (0, 0, 0)  // top-left, right
limit = 2

Simulation:
1. (0,0) → hit '/' → reflect (count=1)
2. Move to next cell
3. Hit '/' → reflect (count=2)
4. Move to next cell
5. Hit '/' → count=3 > limit=2 → STOP

Returns: 3 cells visited
```

## Files
- `reflection_limit.py` — Python implementation
- `reflection_limit.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part4\reflection_limit.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part4\reflection_limit.cpp -o .\Part4\reflection_limit.exe ; if ($?) { .\Part4\reflection_limit.exe }
```

## Notes
- Reflection limit is a **practical constraint** for real-world beam simulations
- Combines with loop detection: stops on **first** of (loop | limit | exit | wall)
- Part 5 will add grid rotation complexity
- Part 6 will handle multiple queries efficiently
