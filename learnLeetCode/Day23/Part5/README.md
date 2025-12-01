# Day 23 — Part 5: The Mind Labyrinth

Goal: Minimize cost from node 1 to node n where traversing an edge of weight w when the unique-visited count is k adds w·k to total cost. First node counts as visited (k=1).

Assumptions:
- Edges treated as undirected (prompt says weighted graph but not direction); easy to switch to directed by removing the symmetric insert.
- Heuristic per prompt hint: Use Dijkstra on (node, k) states with pruning, not exponential (node, set).

Approach:
- State: (u, k) where k ∈ [1..n]. Dist table dist[u][k] = best-known cost to arrive at u having visited k distinct nodes so far.
- Transitions: to neighbor v with cost w·k (as if already visited) or w·(k+1) (as if new). Keep whichever leads to better dist.
- Pareto pruning via the dist table. Return min dist[n][k] over k, but early-exit when we first pop u=n with minimal d.

Notes:
- This is optimistic since we ignore the exact set of visited nodes; works well with pruning for modest sizes but is not guaranteed to be exact for adversarial graphs.
- To enforce direction, remove the g[v].push_back({u,w}).

Files:
- mind_labyrinth.py — Python version with a small demo.
- mind_labyrinth.cpp — C++17 version.
