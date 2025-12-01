from collections import deque
import copy

def solve_quantum_tile(grid, target_r, target_c, K, M):
    N = len(grid)
    
    # BFS State: (current_grid_tuple, steps)
    # To save space, we might not store full grid in visited if M is small.
    # Or we assume we only modify relevant cells.
    
    # Let's try a BFS that allows modifying (r,c) or its neighbors.
    # Actually, we can modify ANY cell. But that's too broad.
    # Heuristic: We only modify (r,c) or neighbors of (r,c) that match (r,c).
    
    start_grid = [row[:] for row in grid]
    
    # Convert to tuple for hashing
    def to_tuple(g):
        return tuple(tuple(row) for row in g)
    
    queue = deque([(start_grid, 0)])
    visited = set()
    visited.add(to_tuple(start_grid))
    
    # Directions
    dirs = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    def get_cluster(g, r, c):
        val = g[r][c]
        if val == 0: return set([(r, c)]) # 0 doesn't collapse usually? Or does 0 collapse?
        # "If there are three or more tile same... cluster... becomes 0"
        # Usually 0 is "empty" and doesn't collapse further. Let's assume 0 is stable.
        if val == 0: return set()
        
        cluster = set([(r, c)])
        q = deque([(r, c)])
        seen = set([(r, c)])
        
        while q:
            curr_r, curr_c = q.popleft()
            for dr, dc in dirs:
                nr, nc = curr_r + dr, curr_c + dc
                if 0 <= nr < N and 0 <= nc < N:
                    if g[nr][nc] == val and (nr, nc) not in seen:
                        seen.add((nr, nc))
                        cluster.add((nr, nc))
                        q.append((nr, nc))
        return cluster

    def apply_collapse(g):
        # Find all clusters >= 3 and set to 0
        # We need to do this globally or just locally?
        # "After that, entire board performs Quantum Collapse"
        # So we need to check all clusters.
        to_zero = set()
        visited_cells = set()
        
        for r in range(N):
            for c in range(N):
                if (r, c) not in visited_cells and g[r][c] != 0:
                    cluster = get_cluster(g, r, c)
                    visited_cells.update(cluster)
                    if len(cluster) >= 3:
                        to_zero.update(cluster)
                        
        new_g = [row[:] for row in g]
        for r, c in to_zero:
            new_g[r][c] = 0
        return new_g

    while queue:
        curr_grid, steps = queue.popleft()
        
        # Check target
        if curr_grid[target_r][target_c] == K:
            return steps
        
        if steps >= M:
            continue
            
        # Generate next states
        # We can modify (target_r, target_c)
        # Or neighbors?
        # To limit branching factor, let's only consider:
        # 1. Modifying (target_r, target_c)
        # 2. Modifying neighbors of (target_r, target_c) IF they have the same value (to break cluster)
        
        candidates = set([(target_r, target_c)])
        
        # Add neighbors that match current target value (potential cluster members)
        curr_val = curr_grid[target_r][target_c]
        for dr, dc in dirs:
            nr, nc = target_r + dr, target_c + dc
            if 0 <= nr < N and 0 <= nc < N:
                if curr_grid[nr][nc] == curr_val:
                    candidates.add((nr, nc))
                    
        for r, c in candidates:
            # Operation: Double
            next_grid = [row[:] for row in curr_grid]
            next_grid[r][c] = (next_grid[r][c] * 2) % 10
            
            # Collapse
            collapsed_grid = apply_collapse(next_grid)
            
            grid_tuple = to_tuple(collapsed_grid)
            if grid_tuple not in visited:
                visited.add(grid_tuple)
                queue.append((collapsed_grid, steps + 1))
                
    return -1

if __name__ == "__main__":
    grid = [
        [1, 1, 2],
        [1, 5, 5],
        [2, 5, 5]
    ]
    # Target (0,0) to become 4.
    # (0,0) is 1.
    # Step 1: Double (0,0) -> 2. Grid:
    # 2 1 2
    # 1 5 5
    # 2 5 5
    # No collapse (1s are separated, 2s separated, 5s cluster of 4).
    # Wait, 5s cluster of 4 at bottom right?
    # (1,1), (1,2), (2,1), (2,2) are 5. They collapse to 0.
    # Grid becomes:
    # 2 1 2
    # 1 0 0
    # 2 0 0
    # Step 2: Double (0,0) -> 4. Target reached.
    # Total steps: 2.
    
    r, c = 0, 0
    K = 4
    M = 5
    print(f"Min Steps: {solve_quantum_tile(grid, r, c, K, M)}")
