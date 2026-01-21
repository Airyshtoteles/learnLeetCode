import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, K, Start, Target = map(int, line1)
        
        # u -> list of {v, normal, reversed}
        adj = {} 
        
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            
            # u -> v (Normal)
            if u not in adj: adj[u] = {}
            if v not in adj[u]: adj[u][v] = {'n': False, 'r': False}
            adj[u][v]['n'] = True
            
            # v -> u (Reversed)
            if v not in adj: adj[v] = {}
            if u not in adj[v]: adj[v][u] = {'n': False, 'r': False}
            adj[v][u]['r'] = True
            
    except ValueError:
        return

    period = 2 * K
    if period > 14: # Limit state space for Python recursion/memory
        print("NO")
        return

    full_mask = (1 << period) - 1
    queue = deque([(Start, full_mask)])
    visited = {(Start, full_mask)}
    
    possible = False
    
    while queue:
        u, mask = queue.popleft()
        
        if u == Target:
            possible = True
            break
            
        if u in adj:
            for v, props in adj[u].items():
                # Check validity for all phases in mask
                is_valid_move = True
                next_mask = 0
                
                for p in range(period):
                    if (mask >> p) & 1:
                        is_normal_phase = (p < K)
                        allowed = False
                        if is_normal_phase and props['n']: allowed = True
                        if not is_normal_phase and props['r']: allowed = True
                        
                        if not allowed:
                            is_valid_move = False
                            break
                        
                        next_p = (p + 1) % period
                        next_mask |= (1 << next_p)
                
                if is_valid_move:
                    if (v, next_mask) not in visited:
                        visited.add((v, next_mask))
                        queue.append((v, next_mask))

    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
