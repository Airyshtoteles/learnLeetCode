import sys
from collections import deque

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            m = int(next(iterator))
        except StopIteration:
            return
            
        adj = [[] for _ in range(n)]
        for _ in range(m):
            u = int(next(iterator))
            v = int(next(iterator))
            c = int(next(iterator))
            adj[u].append((v, c))
            adj[v].append((u, c))
            
        # BFS
        # State: (u, frozenset of (cooldown, time_left))
        # Using frozenset for hashability
        
        start_timers = frozenset()
        q = deque([(0, start_timers)])
        visited = set([(0, start_timers)])
        
        while q:
            u, timers = q.popleft()
            
            if u == n - 1:
                print("true")
                return
                
            # Convert timers to dict for easier lookup
            timer_dict = dict(timers)
            
            # Prepare next base timers (decrement)
            next_base = {}
            for cd, t in timers:
                if t > 1:
                    next_base[cd] = t - 1
                    
            for v, c in adj[u]:
                # Check if blocked
                if c in timer_dict and timer_dict[c] > 0:
                    continue
                    
                # Create next state
                new_timers = next_base.copy()
                if c > 0:
                    new_timers[c] = c
                    
                # Convert back to frozenset
                next_timers_frozen = frozenset(new_timers.items())
                
                if (v, next_timers_frozen) not in visited:
                    visited.add((v, next_timers_frozen))
                    q.append((v, next_timers_frozen))
                    
        print("false")
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
