import heapq

def solve():
    # Hardcoded Input
    # 3 Realms, 4x4
    # 1 = Floor, 0 = Void
    
    # Realm A
    grid_a = [
        [1, 1, 0, 0],
        [0, 1, 1, 0],
        [0, 0, 1, 0],
        [0, 0, 1, 1]
    ]
    
    # Realm B (Bridge)
    grid_b = [
        [0, 0, 0, 0],
        [1, 1, 1, 1], # Bridge across row 1
        [1, 0, 0, 1],
        [1, 1, 1, 1]
    ]
    
    # Realm C (Goal)
    grid_c = [
        [0, 0, 0, 0],
        [0, 0, 0, 0],
        [0, 1, 1, 1],
        [0, 1, 0, 1]
    ]
    
    realms = [grid_a, grid_b, grid_c]
    N = len(grid_a)
    M = len(grid_a[0])
    
    # Dijkstra
    # State: (cost, r, c, realm_idx)
    pq = [(0, 0, 0, 0)]
    dist = {} # (r, c, realm) -> min_cost
    dist[(0, 0, 0)] = 0
    
    target = (N-1, M-1, 2) # Goal in Realm C
    
    min_cost = -1
    
    while pq:
        d, r, c, k = heapq.heappop(pq)
        
        if d > dist.get((r, c, k), float('inf')):
            continue
        
        if (r, c, k) == target:
            min_cost = d
            break
        
        # 1. Move within realm
        for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M:
                if realms[k][nr][nc] == 1:
                    new_cost = d + 1
                    if new_cost < dist.get((nr, nc, k), float('inf')):
                        dist[(nr, nc, k)] = new_cost
                        heapq.heappush(pq, (new_cost, nr, nc, k))
                        
        # 2. Shift Realm
        nk = (k + 1) % 3
        if realms[nk][r][c] == 1:
            new_cost = d + 3
            if new_cost < dist.get((r, c, nk), float('inf')):
                dist[(r, c, nk)] = new_cost
                heapq.heappush(pq, (new_cost, r, c, nk))
                
    print(f"Minimum Cost: {min_cost}")

if __name__ == "__main__":
    solve()
