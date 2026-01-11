import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, Start, Target = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: Timers = []
        else: Timers = [int(x) for x in line2]
        
        adj = [[] for _ in range(N)]
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            adj[v].append(u) # Undirected
            
    except ValueError:
        return

    Timers.sort()
    
    # BFS
    dist = [-1] * N
    queue = deque([Start])
    dist[Start] = 0
    path_len = -1
    
    while queue:
        u = queue.popleft()
        if u == Target:
            path_len = dist[Target]
            break
            
        for v in adj[u]:
            if dist[v] == -1:
                dist[v] = dist[u] + 1
                queue.append(v)
                
    if path_len == -1:
        print("NO")
        return
        
    # Check robustness
    possible = True
    for i in range(path_len):
        if i >= len(Timers): 
            possible = False; break
        # Arrival time at i-th node in path (excluding start) is i+1
        # Timer assigned is Timers[i] (worst case)
        if Timers[i] <= (i + 1):
            possible = False
            break
            
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
