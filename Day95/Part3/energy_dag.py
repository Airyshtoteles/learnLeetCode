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
        Emax = int(next(iterator))
        T = int(next(iterator))
        
        costs = [0] + [int(next(iterator)) for _ in range(N)]
        
        adj = [[] for _ in range(N + 1)]
        in_degree = [0] * (N + 1)
        
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            adj[u].append(v)
            in_degree[v] += 1
    except StopIteration:
        return

    # Max Heap (negative simulation)
    pq = []
    max_e = [-1] * (N + 1)
    
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            if Emax >= costs[i]:
                next_e = min(Emax, Emax - costs[i] + 1)
                max_e[i] = next_e
                heapq.heappush(pq, (-next_e, i))
                
    while pq:
        neg_e, u = heapq.heappop(pq)
        e = -neg_e
        
        if e < max_e[u]:
            continue
            
        if u == T:
            print("YES")
            return
            
        for v in adj[u]:
            if e >= costs[v]:
                next_e = min(Emax, e - costs[v] + 1)
                if next_e > max_e[v]:
                    max_e[v] = next_e
                    heapq.heappush(pq, (-next_e, v))
                    
    print("NO")

if __name__ == "__main__":
    solve()
