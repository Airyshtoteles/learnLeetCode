import sys
import math
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
    except StopIteration:
        return

    edges = []
    adj = [[] for _ in range(N + 1)]
    
    for _ in range(M):
        u = int(next(iterator))
        v = int(next(iterator))
        r = float(next(iterator))
        edges.append((u, v, r))
        adj[u].append(v)
        
    # Bellman-Ford Maximize Log Sum
    # dist[u] = max log accumulated
    dist = [-float('inf')] * (N + 1)
    dist[1] = 0.0
    
    # Relax N-1 times
    for _ in range(N - 1):
        updated = False
        for u, v, r in edges:
            if dist[u] > -1e15: # Reachable
                w = math.log(r) if r > 0 else -float('inf')
                if dist[u] + w > dist[v] + 1e-9:
                    dist[v] = dist[u] + w
                    updated = True
        if not updated:
            break
            
    # Check cycles
    # Nodes that can still be relaxed are part of positive cycle flow
    in_cycle_flow = [False] * (N + 1)
    queue = deque()
    
    for u, v, r in edges:
        if dist[u] > -1e15:
            w = math.log(r) if r > 0 else -float('inf')
            if dist[u] + w > dist[v] + 1e-9:
                # Cycle detected affecting v
                if not in_cycle_flow[v]:
                    in_cycle_flow[v] = True
                    queue.append(v)
    
    # Propagate cycle flow
    while queue:
        u = queue.popleft()
        for v in adj[u]:
            if not in_cycle_flow[v]:
                in_cycle_flow[v] = True
                queue.append(v)
                
    if in_cycle_flow[N]:
        print("INFINITY")
    else:
        if dist[N] < -1e15:
            print("0.00000")
        else:
            print(f"{math.exp(dist[N]):.5f}")

if __name__ == "__main__":
    solve()
