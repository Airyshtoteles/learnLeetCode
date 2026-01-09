import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, T = map(int, line1)
        
        adj = [[] for _ in range(N)]
        rev_adj = [[] for _ in range(N)]
        all_edges = []
        
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            rev_adj[v].append(u)
            all_edges.append((u, v))
            
    except ValueError:
        return

    # 1. Find Ancestors of T
    is_ancestor = [False] * N
    queue = deque([T])
    is_ancestor[T] = True
    ancestor_count = 0
    
    while queue:
        u = queue.popleft()
        ancestor_count += 1
        for v in rev_adj[u]:
            if not is_ancestor[v]:
                is_ancestor[v] = True
                queue.append(v)
                
    # 2. In-degrees for induced subgraph
    in_degree = [0] * N
    for u, v in all_edges:
        if is_ancestor[u] and is_ancestor[v]:
            in_degree[v] += 1
            
    # 3. Kahn's Algo check
    topo_q = deque()
    for i in range(N):
        if is_ancestor[i] and in_degree[i] == 0:
            topo_q.append(i)
            
    processed = 0
    valid = True
    
    while topo_q:
        if len(topo_q) > 1:
            valid = False
            break
            
        u = topo_q.popleft()
        processed += 1
        
        for v in adj[u]:
            if is_ancestor[v]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    topo_q.append(v)
                    
    if valid and processed == ancestor_count:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
