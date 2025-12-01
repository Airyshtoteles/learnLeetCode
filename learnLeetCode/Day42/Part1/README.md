# Arena Echoes — Min-Cost Zero Attribute Path

Level: Hard

You are in a directed graph with N nodes and M portals (edges). Each edge `(u -> v)` has a 60-bit attribute mask `attr`. You start at node `0` with current attribute `0`. When traversing an edge with attribute `a`, your current attribute becomes `cur ^ a`. The cost of each step is `popcount(cur ^ a)` (i.e., popcount of the attribute after applying the edge). You may revisit nodes/edges arbitrarily.

Goal: reach node `N-1` with final attribute exactly `0` and minimize the total cost. If impossible, return `-1`.

## Observation
- The path cost is the sum over steps of popcount of the prefix-XOR states along the path.
- A straightforward state space for Dijkstra is `(node, cur_attr)` with edge weight `popcount(cur_attr ^ a)`.
- The attribute space is large (up to 2^60), so we must prune states. A practical approach is to record the best cost per `(node, attr)` seen and aggressively prune dominated states, keeping only a limited number per node.
- Dijkstra remains correct provided we only prune states that cannot lead to a better result than the current best target; in practice we cap per-node state map and skip inserting obviously worse states by a margin. This is a heuristic that performs well on sparse instances. If the graph admits an optimal path with states outside the kept set, the heuristic may miss it.

## Algorithm (Practical Dijkstra with Pruning)
- Maintain `dist[node][attr] = best cost` in hash maps per node; also track `bestAtNode[node] = min cost among all attrs`.
- Use a priority queue on `(cost, node, attr)`.
- For each pop, if `(node == N-1 && attr == 0)`, return `cost`.
- Relax neighbors: `nattr = attr ^ edge.attr`, `ncost = cost + popcount(nattr)`.
- Insert if it improves. If per-node map grows beyond a cap (e.g., 512), skip inserting states with `ncost > bestAtNode[node] + margin` (e.g., 64*60).

Complexity (with pruning): roughly `O((states + M) log states)`; states are capped per node.

This implementation prioritizes practicality under constraints `N ≤ 1e5, M ≤ 3e5`.
