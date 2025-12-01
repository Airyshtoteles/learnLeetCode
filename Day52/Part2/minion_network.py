import sys

# Increase recursion depth for deep DFS
sys.setrecursionlimit(10000)

def solve_minion_network(n, connections):
    adj = [[] for _ in range(n)]
    rev_adj = [[] for _ in range(n)]
    
    for u, v in connections:
        adj[u].append(v)
        rev_adj[v].append(u)
        
    # Kosaraju's Algorithm
    visited = [False] * n
    stack = []
    
    def dfs1(u):
        visited[u] = True
        for v in adj[u]:
            if not visited[v]:
                dfs1(v)
        stack.append(u)
        
    for i in range(n):
        if not visited[i]:
            dfs1(i)
            
    # Second pass on reverse graph
    visited = [False] * n
    sccs = []
    scc_id = [-1] * n
    
    def dfs2(u, current_scc):
        visited[u] = True
        scc_id[u] = len(sccs)
        current_scc.append(u)
        for v in rev_adj[u]:
            if not visited[v]:
                dfs2(v, current_scc)
                
    while stack:
        u = stack.pop()
        if not visited[u]:
            current_scc = []
            dfs2(u, current_scc)
            sccs.append(current_scc)
            
    num_sccs = len(sccs)
    if num_sccs == 1:
        return 0
        
    # Build Condensation Graph
    scc_in_degree = [0] * num_sccs
    scc_out_degree = [0] * num_sccs
    
    # Use a set to avoid duplicate edges in condensation graph
    scc_edges = set()
    
    for u in range(n):
        u_scc = scc_id[u]
        for v in adj[u]:
            v_scc = scc_id[v]
            if u_scc != v_scc:
                if (u_scc, v_scc) not in scc_edges:
                    scc_edges.add((u_scc, v_scc))
                    scc_out_degree[u_scc] += 1
                    scc_in_degree[v_scc] += 1
                    
    sources = 0
    sinks = 0
    
    for i in range(num_sccs):
        if scc_in_degree[i] == 0:
            sources += 1
        if scc_out_degree[i] == 0:
            sinks += 1
            
    return max(sources, sinks)

if __name__ == "__main__":
    # Example 1: 0->1->2->0 (Cycle)
    # Already SC.
    n1 = 3
    conn1 = [(0, 1), (1, 2), (2, 0)]
    print(f"Min Edges (Ex 1): {solve_minion_network(n1, conn1)}")
    
    # Example 2: 0->1, 2->3. Disconnected components.
    # SCCs: {0}, {1}, {2}, {3}.
    # Edges: 0->1, 2->3.
    # Condensation: 0->1, 2->3.
    # Sources: 0, 2 (Count 2).
    # Sinks: 1, 3 (Count 2).
    # Max(2, 2) = 2.
    # Add 1->2 and 3->0? -> 0->1->2->3->0. Yes.
    n2 = 4
    conn2 = [(0, 1), (2, 3)]
    print(f"Min Edges (Ex 2): {solve_minion_network(n2, conn2)}")
    
    # Example 3: 0->1, 0->2.
    # SCCs: {0}, {1}, {2}.
    # Edges: 0->1, 0->2.
    # Sources: 0 (Count 1).
    # Sinks: 1, 2 (Count 2).
    # Max(1, 2) = 2.
    # Add 1->0, 2->0? No, that makes 0 reachable from all, but 1 can't reach 2.
    # Add 1->2, 2->0. Cycle 0->1->2->0.
    n3 = 3
    conn3 = [(0, 1), (0, 2)]
    print(f"Min Edges (Ex 3): {solve_minion_network(n3, conn3)}")
