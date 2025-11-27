from collections import deque

def solve_gravity_flip(grid):
    N = len(grid)
    M = len(grid[0])
    
    start_pos = None
    target_pos = None
    
    for r in range(N):
        for c in range(M):
            if grid[r][c] == 'S':
                start_pos = (r, c)
            elif grid[r][c] == 'T':
                target_pos = (r, c)
                
    # Directions: Down, Up, Right, Left
    # Indices: 0, 1, 2, 3
    dirs = [(1, 0), (-1, 0), (0, 1), (0, -1)]
    
    # Helper to simulate falling
    def fall(r, c, g_idx):
        dr, dc = dirs[g_idx]
        curr_r, curr_c = r, c
        
        while True:
            if (curr_r, curr_c) == target_pos:
                return curr_r, curr_c, True
            
            nr, nc = curr_r + dr, curr_c + dc
            
            if not (0 <= nr < N and 0 <= nc < M) or grid[nr][nc] == '#':
                return curr_r, curr_c, False
            
            curr_r, curr_c = nr, nc

    # Initial State
    # Start with Gravity Down (0)
    # First, fall from Start
    start_r, start_c, hit_t = fall(start_pos[0], start_pos[1], 0)
    if hit_t: return 0
    
    # Queue: (r, c, g_idx)
    # Dist: dist[r][c][g_idx]
    queue = deque([(start_r, start_c, 0)])
    dist = {}
    dist[(start_r, start_c, 0)] = 0
    
    while queue:
        r, c, g = queue.popleft()
        d = dist[(r, c, g)]
        
        if (r, c) == target_pos:
            return d
        
        # 1. Walk (Cost 0)
        # Perpendicular directions
        if g in [0, 1]: # Vertical Gravity -> Walk Horizontal
            walk_dirs = [2, 3]
        else: # Horizontal Gravity -> Walk Vertical
            walk_dirs = [0, 1]
            
        for w_idx in walk_dirs:
            dr, dc = dirs[w_idx]
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#':
                # Check support: cell in gravity direction from nr, nc
                gr, gc = dirs[g]
                support_r, support_c = nr + gr, nc + gc
                
                has_support = False
                if not (0 <= support_r < N and 0 <= support_c < M):
                    has_support = True # Boundary acts as support? Or void?
                    # Usually boundary is void/death or wall. 
                    # Problem says "boundary". Let's assume boundary is wall for support?
                    # Or maybe "fall until hit wall or boundary".
                    # If boundary, you stop. So boundary supports you.
                    has_support = True
                elif grid[support_r][support_c] == '#':
                    has_support = True
                elif (support_r, support_c) == target_pos:
                     # If support is target, we might fall into it?
                     # But we are checking support for WALKING.
                     pass
                
                if has_support:
                    # Walk safely
                    if (nr, nc, g) not in dist or dist[(nr, nc, g)] > d:
                        dist[(nr, nc, g)] = d
                        queue.appendleft((nr, nc, g))
                else:
                    # Walk off ledge -> Fall
                    fr, fc, hit = fall(nr, nc, g)
                    if hit: return d # Reached target during fall
                    
                    if (fr, fc, g) not in dist or dist[(fr, fc, g)] > d:
                        dist[(fr, fc, g)] = d
                        queue.appendleft((fr, fc, g))

        # 2. Flip Gravity (Cost 1)
        for new_g in range(4):
            if new_g == g: continue
            
            fr, fc, hit = fall(r, c, new_g)
            new_cost = d + 1
            
            if hit: return new_cost
            
            if (fr, fc, new_g) not in dist or dist[(fr, fc, new_g)] > new_cost:
                dist[(fr, fc, new_g)] = new_cost
                queue.append((fr, fc, new_g))
                
    return -1

if __name__ == "__main__":
    Grid = [
        "S....",
        "###.#",
        "....T",
        "#####"
    ]
    result = solve_gravity_flip(Grid)
    print(f"Minimum Energy: {result}")
