import sys
from collections import deque

def solve():
    try:
        input_data = sys.stdin.read().split()
    except Exception:
        return

    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        K = int(next(iterator))
        C_cooldown = int(next(iterator))
        N = int(next(iterator))
        M = int(next(iterator))
        Target = int(next(iterator))
        
        starts = []
        for _ in range(K):
            starts.append(int(next(iterator)))
            
        adj = [[] for _ in range(N + 1)]
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            adj[u].append(v)
            adj[v].append(u) # Undirected
            
    except StopIteration:
        return

    possible = False
    
    for start_node in starts:
        queue = deque([start_node])
        visited = {start_node}
        reached = False
        
        if start_node == Target:
            possible = True
            break
            
        while queue:
            u = queue.popleft()
            if u == Target:
                reached = True
                break
            
            for v in adj[u]:
                if v not in visited:
                    visited.add(v)
                    queue.append(v)
        
        if reached:
            possible = True
            break
            
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
