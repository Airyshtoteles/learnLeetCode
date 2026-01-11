import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, Start, Target = map(int, line1)
        
        adj = [[] for _ in range(N)]
        for _ in range(M):
            line = sys.stdin.readline().split()
            if not line: break
            u, v = map(int, line)
            adj[u].append(v)
            
    except ValueError:
        return

    queue = deque([Start])
    visited = {Start}
    possible = False
    
    while queue:
        u = queue.popleft()
        if u == Target:
            possible = True
            break
            
        for v in adj[u]:
            if v not in visited:
                visited.add(v)
                queue.append(v)
                
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
