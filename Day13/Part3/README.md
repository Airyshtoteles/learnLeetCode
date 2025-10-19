# Day 13 — Part 3: Loop Detection

**Problem**: Detect if a light beam gets trapped in an **infinite reflection loop**. Return `-1` if loop detected, otherwise return cells visited.

## What is a Loop?
A loop occurs when the beam revisits the **same state** `(row, col, direction)`:
- Same position
- Same direction
- This means the beam will repeat the exact same path infinitely

## Why Loops Happen
Mirrors can create closed reflection circuits:
```
/.\ 
.#.
\./
```
A beam entering from top-left can bounce between mirrors indefinitely without exiting.

## Approach (State Tracking)
1. Track **visited states**: set of `(row, col, dir)` tuples
2. At each step:
   - Check if current state was visited before
   - If yes → **loop detected**, return `-1`
   - If no → add to visited states, continue simulation
3. If beam exits grid or hits wall → return cell count

### Key Insight
- **Visited cells** tracks which positions were touched (for counting)
- **Visited states** tracks full state `(r, c, dir)` for loop detection
- A cell can be visited with **different directions** (not a loop)
- Only **same state** indicates a loop

## Complexity
- **Time**: O(n × m × 4) — worst case visits each cell in each direction once
- **Space**: O(n × m × 4) — visited states set

## Example: Loop
```
Input:
grid = [
  "/\\",
  "\\/"
]
entry = (0, 0, 0)  // top-left, direction right

Simulation:
1. (0,0) dir=0 (→)
2. (0,1) dir=0, hits '\' → reflect to dir=1 (↓)
3. (1,1) dir=1, hits '/' → reflect to dir=2 (←)
4. (1,0) dir=2, hits '\' → reflect to dir=3 (↑)
5. (0,0) dir=3, hits '/' → reflect to dir=0 (→)
6. (0,1) dir=0 ← SAME AS STEP 2! Loop detected!

Return: -1
```

## Example: No Loop (Exits)
```
Input:
grid = [
  "...",
  "./.",
  "..."
]
entry = (1, 0, 0)  // middle-left, direction right

Simulation:
1. (1,0) → (1,1) → hits '/' → reflect up
2. (0,1) → exits grid at top

Cells: {(1,0), (1,1), (0,1)} = 3
Return: 3
```

## Files
- `loop_detection.py` — Python implementation
- `loop_detection.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part3\loop_detection.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part3\loop_detection.cpp -o .\Part3\loop_detection.exe ; if ($?) { .\Part3\loop_detection.exe }
```

## Notes
- Loop detection is critical for avoiding infinite simulation
- State tracking ensures O(n×m×4) bounded runtime
- Part 4 will add reflection limit to force termination
- Part 5 will add grid rotation complexity
