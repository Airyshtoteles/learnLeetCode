# Day 13 — Part 1: Mirror Labyrinth — Basic Simulation

**Problem**: Simulate a light beam traveling through a mirror maze and count unique cells visited.

## Grid Elements
- `'/'` → Mirror reflecting diagonally ↗↙
  - Right → Up, Down → Left
  - Left → Down, Up → Right
- `'\'` → Mirror reflecting diagonally ↖↘
  - Right → Down, Down → Right
  - Left → Up, Up → Left
- `'.'` → Empty space (beam continues straight)
- `'#'` → Wall (beam stops)

## Direction Encoding
- `0` = Right (→)
- `1` = Down (↓)
- `2` = Left (←)
- `3` = Up (↑)

## Approach (State-Based Simulation)
1. Start at entry point `(r, c, dir)`
2. Track visited cells in a set
3. At each step:
   - Check bounds (if outside, stop)
   - Check wall (if `#`, stop)
   - Add current cell to visited set
   - Apply mirror reflection if on `'/'` or `'\'`
   - Move in current direction
4. Return count of unique cells visited

### Mirror Reflection Rules
**For `/` mirror**:
- Right (0) → Up (3)
- Down (1) → Left (2)
- Left (2) → Down (1)
- Up (3) → Right (0)

**For `\` mirror**:
- Right (0) → Down (1)
- Down (1) → Right (0)
- Left (2) → Up (3)
- Up (3) → Left (2)

## Complexity
- **Time**: O(n × m × 4) — worst case visits each cell in each direction
- **Space**: O(n × m × 4) — track visited states (r, c, dir)

## Example
```
Input:
grid = [
  ".....",
  "../..",
  "....."
]
entry = (1, 0, 0)  // row 1, col 0, direction right

Simulation:
- Start: (1,0) dir=0 (→)
- Move: (1,1) dir=0 (→)
- Hit mirror '/': reflect to dir=3 (↑)
- Move: (0,1) dir=3 (↑)
- Move: (-1,1) → out of bounds, stop

Cells visited: {(1,0), (1,1), (0,1)} = 3 cells
```

## Files
- `mirror_basic.py` — Python implementation
- `mirror_basic.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part1\mirror_basic.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part1\mirror_basic.cpp -o .\Part1\mirror_basic.exe ; if ($?) { .\Part1\mirror_basic.exe }
```

## Notes
- Part 1 establishes the core simulation engine
- State tracking `(r, c, dir)` will be crucial for loop detection in Part 3
- Part 2 will extend to multiple entry points
- Part 3 will add explicit loop detection with `-1` return
