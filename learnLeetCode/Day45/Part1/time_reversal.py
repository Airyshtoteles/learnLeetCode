import heapq
import sys

def solve():
    # Hardcoded Input
    # Grid 4x4
    # HP values
    grid = [
        [1, 2, 3, 4],
        [2, 1, 4, 3],
        [3, 4, 1, 2],
        [4, 3, 2, 1]
    ]
    M = len(grid)
    N = len(grid[0])
    
    # Assumption: Damage = Grid[r][c] + Time_Elapsed
    # Time Reversal: Suffix damage = Grid[r][c] (Time reset to 0 relative to suffix? Or just base HP?)
    # Let's assume Reversal resets the HP to base value (Grid[r][c]).
    
    # 1. Forward Dijkstra from (0,0) with Time Penalty
    # dist_fwd[r][c] = min damage to reach (r,c)
    dist_fwd = [[float('inf')] * N for _ in range(M)]
    dist_fwd[0][0] = grid[0][0] # Initial damage at t=0
    
    pq = [(grid[0][0], 0, 0, 0)] # cost, r, c, time
    
    while pq:
        cost, r, c, t = heapq.heappop(pq)
        
        if cost > dist_fwd[r][c]:
            continue
            
        # Moves: Right, Down
        for dr, dc in [(0, 1), (1, 0)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < M and 0 <= nc < N:
                nt = t + 1
                # Damage = Base + Time
                dmg = grid[nr][nc] + nt
                new_cost = cost + dmg
                
                if new_cost < dist_fwd[nr][nc]:
                    dist_fwd[nr][nc] = new_cost
                    heapq.heappush(pq, (new_cost, nr, nc, nt))
                    
    # 2. Backward Dijkstra from (M-1, N-1) with Base HP (Reversal Effect)
    # We want min cost from (r,c) to End using Base HP.
    # This is equivalent to shortest path on static grid.
    # We can run backwards from End.
    dist_bwd = [[float('inf')] * N for _ in range(M)]
    
    # Note: When we are at (r,c), we have already paid for (r,c) in the Forward pass.
    # The Suffix starts AFTER (r,c).
    # So dist_bwd[r][c] should represent cost from (r,c)'s neighbors to End.
    # Or we can include (r,c) and subtract later.
    # Let's define dist_bwd[r][c] as cost from (r,c) to End including (r,c).
    # But wait, if we split at U, U is part of Prefix.
    # Suffix is U -> ... -> E (excluding U).
    # So we want path from neighbors of U to E.
    
    dist_bwd[M-1][N-1] = grid[M-1][N-1]
    pq = [(grid[M-1][N-1], M-1, N-1)]
    
    while pq:
        cost, r, c = heapq.heappop(pq)
        
        if cost > dist_bwd[r][c]:
            continue
            
        # Moves: Left, Up (Reverse of Right, Down)
        for dr, dc in [(0, -1), (-1, 0)]:
            nr, nc = r + dr, c + dc
            if 0 <= nr < M and 0 <= nc < N:
                # Cost to enter (r,c) from (nr,nc) is grid[r][c]
                # But here we are accumulating from End.
                # Path: nr,nc -> r,c -> ...
                # Cost added is grid[nr][nc].
                new_cost = cost + grid[nr][nc]
                
                if new_cost < dist_bwd[nr][nc]:
                    dist_bwd[nr][nc] = new_cost
                    heapq.heappush(pq, (new_cost, nr, nc))
                    
    # 3. Combine
    min_total = float('inf')
    
    for r in range(M):
        for c in range(N):
            # Split at (r,c).
            # Prefix cost: dist_fwd[r][c] (includes (r,c))
            # Suffix cost: Path from (r,c) to End, excluding (r,c).
            # dist_bwd[r][c] includes (r,c).
            # So Suffix = dist_bwd[r][c] - grid[r][c].
            
            if dist_fwd[r][c] != float('inf') and dist_bwd[r][c] != float('inf'):
                total = dist_fwd[r][c] + (dist_bwd[r][c] - grid[r][c])
                if total < min_total:
                    min_total = total
                    
    print(f"Minimum Damage: {min_total}")

if __name__ == "__main__":
    solve()
