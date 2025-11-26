import heapq

def solve_quantum_mirror(n, m, grid_r, gates):
    # Gates dictionary: (r, c) -> cost
    gate_costs = {}
    for r, c, cost in gates:
        gate_costs[(r, c)] = cost
        
    # Priority Queue: (cost, r, c, world)
    # world: 0 = Real, 1 = Mirror
    pq = [(0, 0, 0, 0)]
    
    # Distances: (r, c, world) -> min_cost
    dist = {}
    dist[(0, 0, 0)] = 0
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while pq:
        cost, r, c, w = heapq.heappop(pq)
        
        # Target: (N-1, M-1) in Mirror World (w=1)
        if r == n - 1 and c == m - 1 and w == 1:
            return cost
        
        if cost > dist.get((r, c, w), float('inf')):
            continue
        
        # 1. Move to neighbors
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < m:
                # Check safety in current world
                # In Real (w=0): Safe if grid_r[nr][nc] == 0
                # In Mirror (w=1): Safe if grid_r[nr][nc] == 1 (Inverse)
                
                is_safe = False
                if w == 0:
                    if grid_r[nr][nc] == 0:
                        is_safe = True
                else:
                    if grid_r[nr][nc] == 1:
                        is_safe = True
                        
                if is_safe:
                    new_cost = cost + 1
                    if new_cost < dist.get((nr, nc, w), float('inf')):
                        dist[(nr, nc, w)] = new_cost
                        heapq.heappush(pq, (new_cost, nr, nc, w))
                        
        # 2. Switch World (if at Gate)
        if (r, c) in gate_costs:
            switch_cost = gate_costs[(r, c)]
            nw = 1 - w
            new_cost = cost + switch_cost
            
            # We can always switch at a gate
            if new_cost < dist.get((r, c, nw), float('inf')):
                dist[(r, c, nw)] = new_cost
                heapq.heappush(pq, (new_cost, r, c, nw))
                
    return -1

if __name__ == "__main__":
    N = 3
    M = 3
    # 0 is safe in R, 1 is blocked in R (safe in M)
    Grid_R = [
        [0, 0, 1],
        [1, 0, 0],
        [1, 1, 1] # (2,2) is 1, so M(2,2) is 0 (Safe)
    ]
    # Gate at (1,1) with cost 5
    Gates = [[1, 1, 5]]
    
    result = solve_quantum_mirror(N, M, Grid_R, Gates)
    print(f"Minimum Cost: {result}")
