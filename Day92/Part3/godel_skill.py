import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, K, T = map(int, line1)
        
        adj = [[] for _ in range(N)]
        rev_adj = [[] for _ in range(N)]
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            rev_adj[v].append(u)
            
        conflicts = [[] for _ in range(N)]
        for _ in range(K):
            u, v = map(int, sys.stdin.readline().split())
            conflicts[u].append(v)
            conflicts[v].append(u)
            
    except ValueError:
        return

    # Prereqs of T
    prereqs = {T}
    queue = deque([T])
    
    while queue:
        u = queue.popleft()
        for v in adj[u]:
            if v not in prereqs:
                prereqs.add(v)
                queue.append(v)
                
    # Forbidden
    forbidden = set()
    for u in prereqs:
        for v in conflicts[u]:
            forbidden.add(v)
            
    # Propagate Forbidden
    queue_f = deque(list(forbidden))
    
    while queue_f:
        u = queue_f.popleft()
        for w in rev_adj[u]:
            if w not in forbidden:
                forbidden.add(w)
                queue_f.append(w)
                
    # Check
    possible = True
    for u in prereqs:
        if u in forbidden:
            possible = False
            break
            
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
