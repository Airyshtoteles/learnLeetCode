# Day 10 — Part 1: Basic Connectivity (MST)

**Problem**: Given `n` nodes (0 to n-1) and a list of edges `edges[i] = [u, v, w]` (undirected with weight `w`), find the minimum total cost to connect all nodes (Minimum Spanning Tree).

## Example
**Input**:
```
n = 4
edges = [[0,1,3],[0,2,5],[1,2,1],[2,3,4]]
```
**Output**: `8`

**Explanation**: MST can use edges `[1,2,1]`, `[0,1,3]`, `[2,3,4]` → total cost 8.

## Approach (Kruskal's Algorithm with Union-Find)
1. Sort all edges by weight (ascending).
2. Use a Union-Find (Disjoint Set Union) data structure to track connected components.
3. For each edge `(u, v, w)`:
   - If `u` and `v` are not yet connected, union them and add `w` to total cost.
   - Stop when we've added `n-1` edges (a spanning tree).
4. If we can't connect all nodes, return -1.

## Complexity
- **Time**: O(E log E) for sorting edges + O(E α(V)) for union-find operations ≈ O(E log E)
- **Space**: O(V + E)

## Files
- `mst.py` — Python implementation with Union-Find and test cases.
- `mst.cpp` — C++17 implementation with Union-Find and sanity checks.

## How to Run
**Python**:
```powershell
python .\Part1\mst.py
```

**C++** (MinGW g++):
```powershell
g++ -std=c++17 -O2 .\Part1\mst.cpp -o .\Part1\mst.exe ; if ($?) { .\Part1\mst.exe }
```
