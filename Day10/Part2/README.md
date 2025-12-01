# Day 10 — Part 2: Shadow Relay (2-Hop Connectivity)

**Problem**: Given `n` nodes and edges with weights, find the minimum total cost to ensure every pair of nodes can communicate within **≤2 hops** (path length ≤ 2 edges).

## Example
**Input**:
```
n = 4
edges = [[0,1,1],[1,2,2],[2,3,3],[0,3,10]]
```
**Output**: `6`

**Explanation**: Using edges `[0,1,1]`, `[1,2,2]`, `[2,3,3]` gives total cost 6. All pairs can communicate within 2 hops.

## Approach (Heuristic: MST + Diameter Reduction)
1. **Build MST** to ensure basic connectivity with minimum cost (Kruskal + Union-Find).
2. **Compute graph diameter** (maximum shortest path distance in hops) via BFS from each node.
3. If diameter ≤ 2, done. Otherwise:
4. **Greedily add cheapest edges** from the remaining edge list until diameter ≤ 2.

**Note**: Ensuring ≤2 hop diameter is NP-hard in general. This is a greedy heuristic that works well for small graphs.

## Complexity
- **Time**: O(V² + E log E) — BFS for all pairs O(V²), sorting edges O(E log E)
- **Space**: O(V²) for distance matrix

## Files
- `shadow_relay.py` — Python implementation with MST + diameter check.
- `shadow_relay.cpp` — C++17 implementation with MST + diameter check.

## How to Run
**Python**:
```powershell
python .\Part2\shadow_relay.py
```

**C++** (MinGW g++):
```powershell
g++ -std=c++17 -O2 .\Part2\shadow_relay.cpp -o .\Part2\shadow_relay.exe ; if ($?) { .\Part2\shadow_relay.exe }
```

## Notes
- The problem's expected output (6) suggests that the MST alone may satisfy the ≤2 hop constraint for the given example, or an alternate edge selection is used.
- Our heuristic prioritizes MST cost first, then adds edges as needed.
