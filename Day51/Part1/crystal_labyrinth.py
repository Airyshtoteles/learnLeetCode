from collections import deque

def solve_crystal_labyrinth(grid, K):
    N = len(grid)
    M = len(grid[0])
    
    start_pos = None
    end_pos = None
    teleports = []
    crystals = [] # (r, c, value)
    
    for r in range(N):
        for c in range(M):
            cell = grid[r][c]
            if cell == 'S':
                start_pos = (r, c)
            elif cell == 'E':
                end_pos = (r, c)
            elif cell == 'T':
                teleports.append((r, c))
            elif '1' <= cell <= '9':
                crystals.append((r, c, int(cell)))
                
    num_crystals = len(crystals)
    
    # Map (r, c) to crystal index
    crystal_map = {}
    for i, (r, c, val) in enumerate(crystals):
        crystal_map[(r, c)] = i
        
    # BFS State: (r, c, mask) -> min_steps
    # Initialize with infinity
    # Using a dictionary or 3D array? 3D array is faster.
    # dist[r][c][mask]
    # But mask can be up to 2^9 = 512.
    
    # Optimization: If K is small, maybe we don't visit all states?
    # But K can be large.
    
    queue = deque()
    
    # Initial state
    start_mask = 0
    if start_pos in crystal_map:
        start_mask |= (1 << crystal_map[start_pos])
        
    queue.append((start_pos[0], start_pos[1], start_mask, 0))
    
    visited = set() # (r, c, mask)
    visited.add((start_pos[0], start_pos[1], start_mask))
    
    max_value = -1
    
    # Directions
    dirs = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while queue:
        r, c, mask, steps = queue.popleft()
        
        # Check if reached E
        if (r, c) == end_pos:
            # Calculate value
            current_val = 0
            for i in range(num_crystals):
                if (mask >> i) & 1:
                    current_val += crystals[i][2]
            max_value = max(max_value, current_val)
            
        if steps >= K:
            continue
            
        # Generate next moves
        next_positions = []
        
        # 1. Normal moves
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#':
                next_positions.append((nr, nc))
                
        # 2. Teleport
        # If current is T, we can instantly be at any other T
        # But "Teleport tidak menghitung langkah".
        # This means if we are at T, we are effectively at ALL Ts simultaneously for 0 cost.
        # So from a T, we can move to neighbors of ANY T.
        # Or simpler: If we step ONTO a T, we add all Ts to the queue with same steps?
        # Wait, if we step onto T at step S, we are at all Ts at step S.
        # So we should expand from all Ts.
        # To avoid infinite loops, we handle this carefully.
        # Better: If grid[r][c] == 'T', we add all other Ts to queue with SAME steps and SAME mask?
        # Yes, but mark them visited to avoid cycles.
        
        if grid[r][c] == 'T':
            for tr, tc in teleports:
                if (tr, tc) == (r, c): continue
                if (tr, tc, mask) not in visited:
                    visited.add((tr, tc, mask))
                    queue.appendleft((tr, tc, mask, steps)) # 0 cost, push front
                    
        for nr, nc in next_positions:
            new_mask = mask
            if (nr, nc) in crystal_map:
                new_mask |= (1 << crystal_map[(nr, nc)])
                
            if (nr, nc, new_mask) not in visited:
                visited.add((nr, nc, new_mask))
                queue.append((nr, nc, new_mask, steps + 1))
                
    return max_value if max_value != -1 else 0

if __name__ == "__main__":
    grid = [
        ['S', '.', '1', '#', 'E'],
        ['.', '#', '.', '#', '.'],
        ['T', '.', '2', '.', 'T']
    ]
    K = 10
    # Path: S(0,0) -> (0,1) -> (0,2)[Get 1] -> (1,2) -> (2,2)[Get 2] -> (2,1) -> (2,0)[T] -> Teleport to (2,4)[T] -> (1,4) -> (0,4)[E]
    # Steps: 1, 2, 3, 4, 5, 6 (at T), 6 (at T2), 7, 8. Total 8 steps.
    # Value: 1 + 2 = 3.
    
    print(f"Max Value: {solve_crystal_labyrinth(grid, K)}")
