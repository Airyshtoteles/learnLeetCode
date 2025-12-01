"""
Day 10 — Part 1: Basic Connectivity (Minimum Spanning Tree)

Given n nodes and edges with weights, find minimum total cost to connect all nodes.

Approach: Kruskal's algorithm with Union-Find (Disjoint Set Union)
- Sort edges by weight
- For each edge (u, v, w), if u and v not yet connected, union them and add w to cost
- Time: O(E log E), Space: O(V + E)
"""
from typing import List


class UnionFind:
    def __init__(self, n: int):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int) -> bool:
        px, py = self.find(x), self.find(y)
        if px == py:
            return False
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True


def minimum_spanning_tree(n: int, edges: List[List[int]]) -> int:
    """Returns minimum cost to connect all n nodes."""
    edges_sorted = sorted(edges, key=lambda e: e[2])
    uf = UnionFind(n)
    total_cost = 0
    edges_used = 0
    for u, v, w in edges_sorted:
        if uf.union(u, v):
            total_cost += w
            edges_used += 1
            if edges_used == n - 1:
                break
    # If we didn't use n-1 edges, graph is disconnected
    return total_cost if edges_used == n - 1 else -1


if __name__ == "__main__":
    # Example from problem
    n = 4
    edges = [[0,1,3],[0,2,5],[1,2,1],[2,3,4]]
    result = minimum_spanning_tree(n, edges)
    assert result == 8, f"Expected 8, got {result}"

    # Additional test
    assert minimum_spanning_tree(3, [[0,1,1],[1,2,2],[0,2,3]]) == 3
    assert minimum_spanning_tree(2, [[0,1,5]]) == 5

    print("Day10 Part1 mst.py: all tests passed")
