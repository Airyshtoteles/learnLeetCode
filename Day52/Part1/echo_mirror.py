from collections import deque

def solve_echo_mirror(grid):
    R = len(grid)
    C = len(grid[0])
    
    start_p = None
    start_b = None
    exit_pos = None
    
    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'P':
                start_p = (r, c)
            elif grid[r][c] == 'B':
                start_b = (r, c)
            elif grid[r][c] == 'E':
                exit_pos = (r, c)
                
    if start_p == start_b:
        return -1 # Already caught
        
    # BFS
    # State: (pr, pc, br, bc)
    queue = deque([(start_p[0], start_p[1], start_b[0], start_b[1], 0)])
    visited = set([(start_p[0], start_p[1], start_b[0], start_b[1])])
    
    # Directions: U, D, L, R
    # Player deltas
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    # Boss deltas (Mirrored: D, U, R, L)
    # U -> D (1, 0)
    # D -> U (-1, 0)
    # L -> R (0, 1)
    # R -> L (0, -1)
    b_dr = [1, -1, 0, 0]
    b_dc = [0, 0, 1, -1]
    
    while queue:
        pr, pc, br, bc, steps = queue.popleft()
        
        if (pr, pc) == exit_pos:
            return steps
            
        for i in range(4):
            # Player move
            npr, npc = pr + dr[i], pc + dc[i]
            # Check bounds and wall for Player
            if not (0 <= npr < R and 0 <= npc < C and grid[npr][npc] != '#'):
                npr, npc = pr, pc # Stay
                
            # Boss move
            nbr, nbc = br + b_dr[i], bc + b_dc[i]
            # Check bounds and wall for Boss
            if not (0 <= nbr < R and 0 <= nbc < C and grid[nbr][nbc] != '#'):
                nbr, nbc = br, bc # Stay
                
            # Check collision
            if (npr, npc) == (nbr, nbc):
                continue # Caught, invalid move
                
            if (npr, npc, nbr, nbc) not in visited:
                visited.add((npr, npc, nbr, nbc))
                queue.append((npr, npc, nbr, nbc, steps + 1))
                
    return -1

if __name__ == "__main__":
    # Example 1
    # P . .
    # . # .
    # . B E
    # Player at (0,0), Boss at (2,1), Exit at (2,2)
    # P moves R -> (0,1). Boss moves L -> (2,0).
    # P moves R -> (0,2). Boss moves L -> (2,0) (hit wall? no, (2,0) is valid).
    # P moves D -> (1,2). Boss moves U -> (1,0).
    # P moves D -> (2,2) (Exit). Boss moves U -> (0,0).
    # Steps: 4?
    
    grid1 = [
        "P..",
        ".#.",
        ".BE"
    ]
    print(f"Min Steps (Ex 1): {solve_echo_mirror(grid1)}")
    
    # Example 2: Trap
    # P B E
    # P moves R -> (0,1). Boss moves L -> (0,0).
    # Collision at (0,1)? No, P is at (0,1), B is at (0,0).
    # Wait, B starts at (0,1). P at (0,0).
    # P moves R -> (0,1). B moves L -> (0,0).
    # Swap positions. Allowed?
    # "If at any point ... occupy the same cell".
    # If they swap, they don't occupy same cell at end of turn.
    # But do they cross?
    # Usually in discrete grid, swap is allowed unless specified.
    # Let's assume swap is allowed.
    
    grid2 = ["PBE"]
    print(f"Min Steps (Ex 2): {solve_echo_mirror(grid2)}")
