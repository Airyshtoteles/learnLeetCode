import sys
from collections import deque, defaultdict

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        Target = int(next(iterator))
        StartTime = int(next(iterator))
        Energy = int(next(iterator))
        M = int(next(iterator))
        
        adj = defaultdict(list)
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            tmin = int(next(iterator))
            tmax = int(next(iterator))
            dt = int(next(iterator))
            c = int(next(iterator))
            adj[u].append((v, tmin, tmax, dt, c))
    except StopIteration:
        return

    # BFS state: (u, t) -> max_energy
    queue = deque([(1, StartTime, Energy)]) # Start Node 1
    max_energy_at = {} 
    max_energy_at[(1, StartTime)] = Energy
    
    while queue:
        u, t, e = queue.popleft()
        
        if e < max_energy_at.get((u, t), -1):
            continue
            
        if u == Target:
            print("YES")
            return
            
        for v, tmin, tmax, dt, cost in adj[u]:
            if tmin <= t <= tmax:
                if e >= cost:
                    nxt_t = t + dt
                    nxt_e = e - cost
                    
                    if max_energy_at.get((v, nxt_t), -1) < nxt_e:
                        max_energy_at[(v, nxt_t)] = nxt_e
                        queue.append((v, nxt_t, nxt_e))
                        
    print("NO")

if __name__ == "__main__":
    solve()
