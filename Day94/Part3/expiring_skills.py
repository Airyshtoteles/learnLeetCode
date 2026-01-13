import sys
from collections import deque
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        expiry = [0] + [int(next(iterator)) for _ in range(N)]
        
        adj = [[] for _ in range(N + 1)]
        rev_adj = [[] for _ in range(N + 1)]
        
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            adj[u].append(v)
            rev_adj[v].append(u)
            
        Target = int(next(iterator))
    except StopIteration:
        return

    # Identify relevant nodes
    relevant = [False] * (N + 1)
    queue = deque([Target])
    relevant[Target] = True
    
    while queue:
        u = queue.popleft()
        for p in rev_adj[u]:
            if not relevant[p]:
                relevant[p] = True
                queue.append(p)
                
    # Subgraph in-degree
    sub_in_degree = [0] * (N + 1)
    for i in range(1, N + 1):
        if relevant[i]:
            for v in adj[i]:
                if relevant[v]:
                    sub_in_degree[v] += 1
                    
    # Priority Queue: (Deadline, ID)
    pq = []
    for i in range(1, N + 1):
        if relevant[i] and sub_in_degree[i] == 0:
            heapq.heappush(pq, (expiry[i], i))
            
    current_time = 1
    
    while pq:
        deadline, u = heapq.heappop(pq)
        
        if current_time > deadline:
            print("NO")
            return
            
        if u == Target:
            print("YES")
            return
            
        current_time += 1
        
        for v in adj[u]:
            if relevant[v]:
                sub_in_degree[v] -= 1
                if sub_in_degree[v] == 0:
                    heapq.heappush(pq, (expiry[v], v))
                    
    print("NO")

if __name__ == "__main__":
    solve()
