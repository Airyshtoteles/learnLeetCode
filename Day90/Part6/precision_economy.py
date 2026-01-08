import sys
from collections import deque

def solve():
    try:
        line = sys.stdin.readline().split()
        if not line: return
        S = int(line[0])
        T = int(line[1])
        Limit = float(line[2])
        Delta = float(line[3])
    except ValueError:
        return

    if S == T:
        print("YES")
        return
        
    if Delta <= 0: # If delta 0, infinite steps if reachability exists. 
        # But let's assume Delta > 0.
        max_steps = 1000000 
    else:
        # Steps * Delta < Limit
        # Steps < Limit / Delta
        val = Limit / Delta
        max_steps = int(val)
        if max_steps * Delta >= Limit:
            max_steps -= 1
            
    if max_steps < 0:
        print("NO")
        return
        
    # BFS
    queue = deque([(S, 0)])
    visited = {S}
    
    possible = False
    
    while queue:
        u, d = queue.popleft()
        
        if u == T:
            possible = True
            break
            
        if d >= max_steps:
            continue
            
        # Ops: +1, *2
        # Pruning: if u > T, cannot reach T (only increasing ops)
        
        next_states = [u + 1, u * 2]
        
        for v in next_states:
            if v <= T: # Optimization for increasing-only ops
                if v not in visited:
                    visited.add(v)
                    queue.append((v, d + 1))
            elif v == T: # Ensure T is caught
                 if v not in visited:
                    visited.add(v)
                    queue.append((v, d + 1))

    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
