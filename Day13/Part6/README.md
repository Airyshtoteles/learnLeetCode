# Day 13 — Part 6: Multi-Query (Ultimate)

**Problem**: Process **Q queries** efficiently, each with parameters `(r, c, dir, limit, rCount)`. Return vector of results.

## Query Format
Each query contains:
- `r, c` = entry position
- `dir` = initial direction (0=right, 1=down, 2=left, 3=up)
- `limit` = max reflections allowed
- `rCount` = number of 90° rotations to apply

## Approach (Cached Rotations)
**Naive**: For each query, rotate grid `rCount` times → O(Q × n × m)

**Optimized**:
1. **Pre-compute all 4 rotations** once (0°, 90°, 180°, 270°)
   - Costs: O(4 × n × m) = O(n × m)
2. For each query:
   - Lookup cached rotation: `rotations[rCount % 4]`
   - Simulate beam on cached grid
   - Costs: O(limit) per query
3. Return all results as vector

### Why Caching Works
- Only 4 unique rotations possible (rotation 4 = rotation 0)
- Multiple queries can share same rotated grid
- Avoids redundant rotation computations

## Complexity
- **Pre-computation**: O(n × m) — compute 4 rotations once
- **Per query**: O(limit) — simulation only
- **Total**: O(n × m + Q × limit)
- **Space**: O(n × m) — store 4 rotated grids

## Example: Multiple Queries
```
Input:
grid = [
  "...",
  "./.",
  "..."
]
queries = [
  (1, 0, 0, 100, 0),  // rCount=0 → use original grid
  (1, 0, 0, 100, 1),  // rCount=1 → use 90° rotation
  (1, 0, 0, 100, 2),  // rCount=2 → use 180° rotation
  (0, 0, 1, 50, 0),   // Different entry, rCount=0
  (2, 2, 2, 100, 1),  // rCount=1 (reuse cached 90° rotation)
]

Output: [3, 5, 3, 2, 4]  // results for each query
```

## Optimization Highlights
1. **Rotation caching**: Avoids O(Q × n × m) redundant rotations
2. **Independent queries**: Each query processes separately (parallelizable)
3. **Bounded simulation**: Reflection limit ensures O(limit) per query

## Files
- `multi_query.py` — Python implementation
- `multi_query.cpp` — C++17 implementation

## How to Run

**Python**:
```powershell
python .\Part6\multi_query.py
```

**C++**:
```powershell
g++ -std=c++17 -O2 .\Part6\multi_query.cpp -o .\Part6\multi_query.exe ; if ($?) { .\Part6\multi_query.exe }
```

## Notes
- Part 6 completes Day13 "Mirror Labyrinth" challenge!
- Combines all previous parts: simulation, loops, limits, rotation, queries
- Production-ready with efficient caching and bounded complexity
- Can handle large Q (multiple queries) efficiently

## Day 13 Complete Summary
- **Part 1**: Basic beam simulation ✅
- **Part 2**: Multiple entry points ✅
- **Part 3**: Loop detection (return -1) ✅
- **Part 4**: Reflection limit ✅
- **Part 5**: Grid rotation ✅
- **Part 6**: Multi-query with caching ✅
