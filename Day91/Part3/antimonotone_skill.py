import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, T = map(int, line1)
        
        adj = [[] for _ in range(N)]
        in_degree = [0] * N
        
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            in_degree[v] += 1
            
    except ValueError:
        return

    queue = deque()
    visited = [False] * N
    
    for i in range(N):
        if in_degree[i] == 0:
            queue.append(i)
            visited[i] = True
            
    possible = False
    
    while queue:
        u = queue.popleft()
        if u == T:
            possible = True
            break
            
        for v in adj[u]:
            if not visited[v]:
                visited[v] = True
                queue.append(v)
                
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
