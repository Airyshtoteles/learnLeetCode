from collections import deque

def solve_virus_containment(n, connections, infected, critical):
    # Check if any critical node is already infected (should not happen based on constraints)
    infected_set = set(infected)
    for c in critical:
        if c in infected_set:
            return -1
            
    # Build Flow Network
    # Nodes 0 to n-1 are servers.
    # Node n is Source (S).
    # Node n+1 is Sink (T).
    S = n
    T = n + 1
    capacity = [[0] * (n + 2) for _ in range(n + 2)]
    graph = [[] for _ in range(n + 2)]
    
    def add_edge(u, v, cap):
        graph[u].append(v)
        graph[v].append(u) # Residual
        capacity[u][v] = cap
        # capacity[v][u] is 0 initially for directed, but here connections are undirected.
        # Wait, undirected edge (u, v) with capacity 1 means we can flow 1 from u to v OR v to u?
        # Or does it mean we can cut it?
        # If we cut (u, v), we remove the link.
        # In flow network, undirected edge (u, v) is usually modeled as u->v cap 1 AND v->u cap 1.
        # If we saturate u->v, we cut it in that direction.
        # But cutting the physical link stops flow in BOTH directions.
        # However, for separation, if we cut the flow from S to T, we effectively separate them.
        # So yes, u->v cap 1 and v->u cap 1 is correct.
        capacity[v][u] = cap
        
    # Add edges from S to Infected
    for i in infected:
        add_edge(S, i, float('inf'))
        
    # Add edges from Critical to T
    for c in critical:
        add_edge(c, T, float('inf'))
        
    # Add network connections
    for u, v in connections:
        add_edge(u, v, 1)
        
    # Edmonds-Karp Max Flow
    max_flow = 0
    
    while True:
        parent = [-1] * (n + 2)
        queue = deque([S])
        parent[S] = S
        
        path_found = False
        while queue:
            u = queue.popleft()
            if u == T:
                path_found = True
                break
            
            for v in graph[u]:
                if parent[v] == -1 and capacity[u][v] > 0:
                    parent[v] = u
                    queue.append(v)
        
        if not path_found:
            break
            
        # Find bottleneck
        path_flow = float('inf')
        v = T
        while v != S:
            u = parent[v]
            path_flow = min(path_flow, capacity[u][v])
            v = u
            
        max_flow += path_flow
        
        # Update residual capacities
        v = T
        while v != S:
            u = parent[v]
            capacity[u][v] -= path_flow
            capacity[v][u] += path_flow
            v = u
            
    return max_flow

if __name__ == "__main__":
    # Example:
    # 0 -- 1 -- 2
    # 0 is Infected. 2 is Critical.
    # Cut (0, 1) or (1, 2). Min cut 1.
    n = 3
    connections = [(0, 1), (1, 2)]
    infected = [0]
    critical = [2]
    
    print(f"Min edges to remove: {solve_virus_containment(n, connections, infected, critical)}")
    
    # Example 2:
    # 0 -- 1 -- 2
    # |    |
    # 3 -- 4
    # Infected: 0. Critical: 2, 4.
    # Paths: 0-1-2, 0-3-4, 0-1-4? (if 1-4 exists? No)
    # Edges: (0,1), (1,2), (0,3), (3,4), (1,4)
    # Cut (0,1) and (0,3)? Cost 2.
    # Or cut (1,2) and (3,4) and (1,4)? Cost 3.
    # Min cut 2.
    
    n2 = 5
    connections2 = [(0, 1), (1, 2), (0, 3), (3, 4), (1, 4)]
    infected2 = [0]
    critical2 = [2, 4]
    print(f"Min edges to remove (Ex 2): {solve_virus_containment(n2, connections2, infected2, critical2)}")
