from collections import deque

def solve_celestial_shifter(grid, K):
    R = len(grid)
    C = len(grid[0])
    
    start_pos = None
    end_pos = None
    
    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'S':
                start_pos = (r, c)
            elif grid[r][c] == 'E':
                end_pos = (r, c)
                
    # Gravity: 0:D, 1:U, 2:L, 3:R
    # Deltas for gravity
    g_dr = [1, -1, 0, 0]
    g_dc = [0, 0, -1, 1]
    
    # Initial State: (r, c, g, flips)
    # g=0 (Down)
    queue = deque([(start_pos[0], start_pos[1], 0, K, 0)]) # r, c, g, flips, steps
    visited = set([(start_pos[0], start_pos[1], 0, K)])
    
    while queue:
        r, c, g, flips, steps = queue.popleft()
        
        if (r, c) == end_pos:
            return steps
            
        # Check if falling
        nr, nc = r + g_dr[g], c + g_dc[g]
        is_falling = False
        
        if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#':
            is_falling = True
            
        if is_falling:
            # Must fall
            if (nr, nc, g, flips) not in visited:
                visited.add((nr, nc, g, flips))
                queue.append((nr, nc, g, flips, steps + 1))
        else:
            # Grounded. Can Walk or Shift.
            
            # 1. Walk (Perpendicular)
            # If G is D(0)/U(1), perp is L(2)/R(3)
            # If G is L(2)/R(3), perp is U(1)/D(0)
            perp_dirs = []
            if g in [0, 1]:
                perp_dirs = [2, 3] # L, R
            else:
                perp_dirs = [0, 1] # D, U (Wait, D is 0, U is 1)
                
            for d in perp_dirs:
                wr, wc = r + g_dr[d], c + g_dc[d] # Use gravity deltas as move deltas
                # Check bounds and wall
                if 0 <= wr < R and 0 <= wc < C and grid[wr][wc] != '#':
                    if (wr, wc, g, flips) not in visited:
                        visited.add((wr, wc, g, flips))
                        queue.append((wr, wc, g, flips, steps + 1))
                        
            # 2. Shift Gravity
            if flips > 0:
                for ng in range(4):
                    if ng != g:
                        if (r, c, ng, flips - 1) not in visited:
                            visited.add((r, c, ng, flips - 1))
                            queue.append((r, c, ng, flips - 1, steps + 1))
                            
    return -1

if __name__ == "__main__":
    # Example 1
    # S . .
    # # # .
    # . . E
    # K = 1
    # Start (0,0). G=Down. Below is #. Grounded.
    # Walk Right -> (0,1). Below #. Grounded.
    # Walk Right -> (0,2). Below .. Falling!
    # Fall -> (1,2). Below .. Falling!
    # Fall -> (2,2) (E).
    # Steps: (0,0)->(0,1) [1] -> (0,2) [2] -> (1,2) [3] -> (2,2) [4].
    grid1 = [
        "S..",
        "##.",
        "..E"
    ]
    print(f"Min Steps (Ex 1): {solve_celestial_shifter(grid1, 1)}")
    
    # Example 2: Need Shift
    # S . #
    # . . #
    # # # E
    # K = 1
    # Start (0,0). G=Down. Below is .. Fall -> (1,0).
    # (1,0). Below is #. Grounded.
    # Walk Right -> (1,1). Below is .. Fall? No, below (1,1) is (2,1) which is #. Grounded.
    # Walk Right -> (1,2) is #. Blocked.
    # At (1,1), Shift Gravity to Right?
    # G=Right. Right of (1,1) is (1,2) #. Grounded.
    # Walk Down (perp to R) -> (2,1) #. Blocked.
    # Walk Up -> (0,1) .. OK.
    # From (0,1), G=Right. Right is #. Grounded.
    # ...
    # Let's try Shift Up at (1,0).
    # G=Up. Up is (0,0) S. Empty. Fall -> (0,0). Loop.
    
    # Let's try a case where shift is needed.
    # S #
    # . #
    # E #
    # G=Down. Fall to (1,0). Fall to (2,0) E. No shift needed.
    
    # S .
    # # .
    # E .
    # G=Down. Grounded at (0,0).
    # Walk R -> (0,1). Fall -> (1,1). Fall -> (2,1).
    # At (2,1), Grounded (bounds).
    # Walk L -> (2,0) E.
    # No shift needed.
    
    # S .
    # . .
    # # E
    # G=Down. Fall -> (1,0). Grounded at (1,0) (below is #).
    # Walk R -> (1,1). Grounded (below is E).
    # Wait, E is empty space? "If cell ... is Empty (., S, E), you must fall".
    # So at (1,1), below is E. Fall -> (2,1) E. Win.
    
    pass
