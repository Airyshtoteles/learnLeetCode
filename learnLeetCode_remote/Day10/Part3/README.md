# Day 10 — Part 3: The Shadow Network (k Relay Nodes + ≤2 Hop)

**Problem**: Given `n` nodes, edges with weights, and an integer `k`, find the minimum total cost to connect all nodes such that:
- **Only k nodes** can act as **relay nodes** (intermediate nodes in communication paths).
- Any two nodes can communicate within **≤2 hops**, using only relay nodes as intermediates.

## Example
**Input**:
```
n = 5
edges = [[0,1,4],[0,2,3],[1,3,2],[2,4,6],[3,4,1]]
k = 2
```
**Output**: `10`

**Explanation**: Activate nodes `[1, 3]` as relays. Use edges `[0,1,4]`, `[1,3,2]`, `[3,4,1]`, `[0,2,3]` → total cost 10. All nodes can communicate within 2 hops via relays.

## Approach (Brute Force for Small Graphs)
1. **Select k nodes** as relay nodes (try all combinations C(n, k)).
2. For each relay configuration:
   - Connect each **non-relay node** to the **cheapest relay** (direct edge).
   - Build an **MST among relay nodes** to ensure they're interconnected.
3. Compute total cost for each configuration.
4. Return the minimum cost.

**Note**: This is NP-hard. For small n (≤20), brute force is feasible. For larger n, use greedy heuristics (e.g., select high-degree or central nodes as relays).

## Complexity
- **Time**: O(C(n,k) × E) for brute force; O(n² + E log E) for greedy heuristic
- **Space**: O(V + E)

## Files
- `shadow_network.py` — Python implementation with brute-force relay selection.
- `shadow_network.cpp` — C++17 implementation with brute-force relay selection.

## How to Run
**Python**:
```powershell
python .\Part3\shadow_network.py
```

**C++** (MinGW g++):
```powershell
g++ -std=c++17 -O2 .\Part3\shadow_network.cpp -o .\Part3\shadow_network.exe ; if ($?) { .\Part3\shadow_network.exe }
```

## Notes
- For k ≥ n, problem reduces to simple MST.
- Algorithm tries all C(n, k) relay combinations; exponential for large n.
- Edge selection prioritizes cheapest edges to relays and among relays (MST).
