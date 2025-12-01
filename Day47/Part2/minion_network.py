class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n
        self.count = n  # Number of disjoint sets

    def find(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.find(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        root_u = self.find(u)
        root_v = self.find(v)

        if root_u != root_v:
            if self.rank[root_u] > self.rank[root_v]:
                self.parent[root_v] = root_u
            elif self.rank[root_u] < self.rank[root_v]:
                self.parent[root_u] = root_v
            else:
                self.parent[root_v] = root_u
                self.rank[root_u] += 1
            self.count -= 1
            return True
        return False

def solve_minion_network(n, connections):
    # Calculate actual costs and prepare edges
    # connections: [u, v, cost, is_corrupted]
    edges = []
    for u, v, cost, is_corrupted in connections:
        actual_cost = cost * 2 if is_corrupted else cost
        edges.append((actual_cost, u, v))
    
    # Sort edges by cost
    edges.sort()
    
    uf = UnionFind(n)
    total_mana = 0
    edges_used = 0
    
    # print(f"Processing {len(edges)} potential connections for {n} outposts...")
    
    for cost, u, v in edges:
        if uf.union(u, v):
            # print(f"  Connecting {u} <-> {v} with cost {cost}")
            total_mana += cost
            edges_used += 1
            
    if uf.count == 1:
        return total_mana
    else:
        return -1

# Test Case
if __name__ == "__main__":
    N = 4
    # [u, v, cost, is_corrupted]
    Connections = [
        [0, 1, 10, 0],
        [1, 2, 20, 1], # Actual 40
        [2, 3, 30, 0],
        [0, 3, 50, 0],
        [1, 3, 5, 0]
    ]
    
    result = solve_minion_network(N, Connections)
    print(f"Minimum Mana Cost: {result}")
