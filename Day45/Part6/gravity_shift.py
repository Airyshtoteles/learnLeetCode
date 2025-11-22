from collections import deque

def solve():
    # Hardcoded Input
    # S . . . #
    # . # . . .
    # . . . # .
    # # . . . G
    # . . . . .
    
    # With 3 shifts, maybe we can slide to G faster?
    
    grid = [
        "S...#",
        ".#...",
        "...#.",
        "#...G",
        "....."
    ]
    M = len(grid)
    N = len(grid[0])
    
    start_pos = None
    goal_pos = None
    
    for r in range(M):
        for c in range(N):
            if grid[r][c] == 'S':
                start_pos = (r, c)
            elif grid[r][c] == 'G':
                goal_pos = (r, c)
                
    # BFS
    # State: (r, c, shifts_left)
    queue = deque()
    queue.append((start_pos[0], start_pos[1], 3, 0)) # r, c, k, steps
    
    visited = set()
    visited.add((start_pos[0], start_pos[1], 3))
    
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while queue:
        r, c, k, steps = queue.popleft()
        
        if (r, c) == goal_pos:
            return steps
        
        # 1. Standard Move
        for dr, dc in moves:
            nr, nc = r + dr, c + dc
            if 0 <= nr < M and 0 <= nc < N and grid[nr][nc] != '#':
                if (nr, nc, k) not in visited:
                    visited.add((nr, nc, k))
                    queue.append((nr, nc, k, steps + 1))
                    
        # 2. Gravity Shift
        if k > 0:
            for dr, dc in moves:
                # Slide
                cr, cc = r, c
                while True:
                    nr, nc = cr + dr, cc + dc
                    if 0 <= nr < M and 0 <= nc < N and grid[nr][nc] != '#':
                        cr, cc = nr, nc
                    else:
                        # Hit wall or boundary
                        break
                
                # If we moved
                if (cr, cc) != (r, c):
                    if (cr, cc, k-1) not in visited:
                        visited.add((cr, cc, k-1))
                        queue.append((cr, cc, k-1, steps + 1))
                        
    return -1

if __name__ == "__main__":
    result = solve()
    print(f"Minimum actions to goal: {result}")
