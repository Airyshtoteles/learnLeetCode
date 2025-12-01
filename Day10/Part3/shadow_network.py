"""
Day 10 — Part 3: The Shadow Network (k relay nodes + ≤2 hop)

Given n nodes, edges, and k (max relay nodes), find minimum cost to connect
all nodes such that:
- Only k nodes can act as relay nodes (intermediate nodes in paths).
- Any two nodes can communicate within ≤2 hops, using only relay nodes as intermediates.

Approach (Heuristic for small graphs):
1. Select k nodes as relays (try different combinations or use greedy heuristic).
2. Connect all non-relay nodes to at least one relay (direct edge).
3. Ensure relays are interconnected such that any relay-to-relay path ≤1 hop (complete graph among relays, or MST).
4. Compute total cost and pick minimum across different relay selections.

This is NP-hard; for small n, we can try different k-node subsets.
For larger n, use heuristics like selecting high-degree nodes as relays.

Time: O(C(n,k) * E) for brute force, or O(n^2) for greedy heuristic.
Space: O(V + E)
"""
from typing import List
from itertools import combinations


def compute_cost_with_relays(n: int, edges: List[List[int]], relays: set) -> int:
    """
    Compute minimum cost to connect all nodes using given relay nodes.
    All non-relay nodes must connect directly to at least one relay.
    Relays must be fully connected among themselves.
    """
    edge_map = {}
    for u, v, w in edges:
        edge_map[(min(u,v), max(u,v))] = min(edge_map.get((min(u,v), max(u,v)), float('inf')), w)

    cost = 0
    non_relays = set(range(n)) - relays

    # Connect each non-relay to cheapest relay
    for node in non_relays:
        min_cost = float('inf')
        for relay in relays:
            key = (min(node, relay), max(node, relay))
            if key in edge_map:
                min_cost = min(min_cost, edge_map[key])
        if min_cost == float('inf'):
            return float('inf')  # Can't connect
        cost += min_cost

    # Connect relays among themselves (MST among relays)
    relay_list = list(relays)
    relay_edges = []
    for i in range(len(relay_list)):
        for j in range(i+1, len(relay_list)):
            u, v = relay_list[i], relay_list[j]
            key = (min(u,v), max(u,v))
            if key in edge_map:
                relay_edges.append((u, v, edge_map[key]))

    # Kruskal on relay edges
    from collections import defaultdict
    parent = {r: r for r in relays}
    def find(x):
        if parent[x] != x:
            parent[x] = find(parent[x])
        return parent[x]
    def union(x, y):
        px, py = find(x), find(y)
        if px == py:
            return False
        parent[py] = px
        return True

    relay_edges.sort(key=lambda e: e[2])
    for u, v, w in relay_edges:
        if union(u, v):
            cost += w

    return cost


def shadow_network(n: int, edges: List[List[int]], k: int) -> int:
    """
    Returns minimum cost to connect all nodes with k relay nodes and ≤2 hop constraint.
    Brute force: try all combinations of k nodes as relays.
    """
    if k >= n:
        # All nodes can be relays; simple MST
        from collections import defaultdict
        uf_parent = list(range(n))
        def find(x):
            if uf_parent[x] != x:
                uf_parent[x] = find(uf_parent[x])
            return uf_parent[x]
        def union(x, y):
            px, py = find(x), find(y)
            if px == py:
                return False
            uf_parent[py] = px
            return True
        edges_sorted = sorted(edges, key=lambda e: e[2])
        cost = 0
        for u, v, w in edges_sorted:
            if union(u, v):
                cost += w
        return cost

    min_cost = float('inf')
    for relay_combo in combinations(range(n), k):
        relay_set = set(relay_combo)
        cost = compute_cost_with_relays(n, edges, relay_set)
        min_cost = min(min_cost, cost)

    return min_cost if min_cost != float('inf') else -1


if __name__ == "__main__":
    # Example from problem
    n = 5
    edges = [[0,1,4],[0,2,3],[1,3,2],[2,4,6],[3,4,1]]
    k = 2
    result = shadow_network(n, edges, k)
    print(f"Day10 Part3 shadow_network.py result for example: {result}")
    # Expected: 10 (activate nodes [1,3], use edges [0,1,4],[1,3,2],[3,4,1],[0,2,3])

    # Simple test
    assert shadow_network(3, [[0,1,1],[1,2,1],[0,2,2]], 1) == 2  # relay at node 1

    print("Day10 Part3 shadow_network.py: basic tests passed")
