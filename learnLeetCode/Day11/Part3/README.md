# Day 11 — Part 3: Hybrid Heuristic (A* with Portals)

**Problem**: Optimized pathfinding in 3D labyrinth using **A\* algorithm** with portal support.

## A\* Algorithm Overview
A\* is an informed search algorithm that uses a **heuristic function** to guide exploration toward the goal.

### Cost Function
```
f(n) = g(n) + h(n)
```
- **g(n)**: Actual cost from start to current position
- **h(n)**: Estimated cost from current position to goal (heuristic)
- **f(n)**: Total estimated cost of path through this position

### Heuristic: 3D Manhattan Distance
```
h(z, x, y) = |z_goal - z| + |x_goal - x| + |y_goal - y|
```
- **Admissible**: Never overestimates the actual cost (guarantees optimality).
- **Consistent**: Satisfies triangle inequality for all neighbors.

## Approach
1. Use a **priority queue** ordered by f(n).
2. Pop position with lowest f(n).
3. For each neighbor (6 directions + portals):
   - Calculate new g(n) and f(n).
   - Add to queue if it improves the path.
4. Stop when goal is reached.

### Portal Handling
- When at a portal (value `2`):
  - Add all other portals to queue with cost `g + k`.
  - Compute f-score using Manhattan distance from portal to goal.

## Complexity
- **Time**: O(n × m × h × log(n × m × h))
  - Priority queue operations: O(log V) per vertex
  - Each cell processed at most once (with best g-score)
- **Space**: O(n × m × h) for visited map and priority queue

## Comparison with BFS
| Algorithm | Time | Space | Optimal | Use Case |
|-----------|------|-------|---------|----------|
| BFS | O(V + E) | O(V) | Yes (unweighted) | All edges cost 1 |
| A\* | O(V log V) | O(V) | Yes (admissible h) | Weighted, large graphs |

**Advantage**: A\* explores fewer nodes by prioritizing promising paths.

## Files
- `labyrinth_astar.py` — Python implementation with heapq
- `labyrinth_astar.cpp` — C++17 implementation with priority_queue

## How to Run

**Python**:
```powershell
python .\Part3\labyrinth_astar.py
```

**C++** (MinGW g++):
```powershell
g++ -std=c++17 -O2 .\Part3\labyrinth_astar.cpp -o .\Part3\labyrinth_astar.exe ; if ($?) { .\Part3\labyrinth_astar.exe }
```

## Example
Same input as Part 2:
```
n=3, m=3, h=2, k=2
Expected output: ~6 (or better with A* pruning)
```

## Notes
- A\* may find the same optimal path as BFS but explores fewer nodes.
- Performance gain is most visible in large, sparse graphs.
- Heuristic quality impacts efficiency (Manhattan is good for grid worlds).
