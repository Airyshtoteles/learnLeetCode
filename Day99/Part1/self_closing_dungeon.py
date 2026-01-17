import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        Start = int(next(iterator))
        Target = int(next(iterator))
        InitHP = int(next(iterator))
        
        adj = [[] for _ in range(N + 1)]
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            min_h = int(next(iterator))
            max_h = int(next(iterator))
            d_h = int(next(iterator))
            adj[u].append((v, min_h, max_h, d_h))
            
    except StopIteration:
        return

    # BFS
    # State: (u, hp)
    queue = deque([(Start, InitHP)])
    visited = set([(Start, InitHP)])
    
    while queue:
        u, hp = queue.popleft()
        
        if u == Target:
            print("YES")
            return
            
        for v, min_h, max_h, d_h in adj[u]:
            if min_h <= hp <= max_h:
                nxt_hp = hp + d_h
                if nxt_hp > 0:
                    if (v, nxt_hp) not in visited:
                        visited.add((v, nxt_hp))
                        queue.append((v, nxt_hp))
                        
    print("NO")

if __name__ == "__main__":
    solve()
