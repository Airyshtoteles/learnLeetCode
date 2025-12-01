import collections

def solve():
    # Hardcoded Input
    N, M = 4, 4
    E = 10
    
    # Cost grid
    costs = [
        [0, 2, 1, 1],
        [1, 5, 1, 1],
        [1, 1, 1, 1],
        [1, 1, 1, 0]
    ]
    # Note: Cost to enter (0,0) is usually irrelevant as we start there, 
    # but let's assume we start with E and only pay when moving INTO a cell.
    # Or pay for start? Usually "enter cell". We are already at start.
    # Let's assume cost is paid when entering.
    
    # Time Gates: (r, c) -> set of forbidden times
    time_gates = {
        (1, 1): {2}, # Cannot enter (1,1) at t=2
        (0, 2): {2}  # Cannot enter (0,2) at t=2
    }
    
    start_pos = (0, 0)
    end_pos = (N-1, M-1)
    
    # BFS State: (r, c, energy, time)
    # Pruning: max_energy[r][c]
    
    max_energy = [[-1] * M for _ in range(N)]
    
    queue = collections.deque()
    
    # Initial state
    # Time 0. Energy E.
    # We are at (0,0).
    queue.append((0, 0, E, 0))
    max_energy[0][0] = E
    
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while queue:
        r, c, cur_e, cur_t = queue.popleft()
        
        if (r, c) == end_pos:
            print(f"Minimum time: {cur_t}")
            return
        
        next_t = cur_t + 1
        
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < N and 0 <= nc < M:
                # Check Time Gate
                if (nr, nc) in time_gates and next_t in time_gates[(nr, nc)]:
                    continue
                
                # Check Energy
                move_cost = costs[nr][nc]
                next_e = cur_e - move_cost
                
                if next_e >= 0:
                    # Pruning
                    if next_e > max_energy[nr][nc]:
                        max_energy[nr][nc] = next_e
                        queue.append((nr, nc, next_e, next_t))
                        
    print("Impossible")

if __name__ == "__main__":
    solve()
