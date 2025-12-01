# Day 32 — Part 2: Minimum Energy Game Map

You have n areas (0 .. n-1) and edges given as [u,v,cost,reward] (bidirectional). Start at 0 with initial energy E. Traversing edge (u,v): requires cost energy available first (energy - cost >= 0) then you gain reward at arrival (energy = min(cap, energy - cost + reward)). Goal: reach node n-1 minimizing total accumulated cost while never letting energy drop below 0.

If impossible, return -1.

Approach:
- State in Dijkstra: (total_cost, node, energy_remaining).
- Energy cap heuristic: cap = E + sum(max(0,reward) over all edges) to bound energy dimension.
- dist[node][energy] = minimal cost found; relax transitions only if energy - cost >= 0.
- Use priority queue on total_cost.
- Answer = min(dist[n-1][e]) across all energy e.

Complexity: O(m * cap * log(n*cap)) in worst case; with small inputs acceptable.

Files:
- minimum_energy_game_map.py — Python Dijkstra variant.
- minimum_energy_game_map.cpp — C++17 implementation.
