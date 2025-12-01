import collections

def solve():
    # Hardcoded Input
    # 6x6 Grid
    grid = [
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0]
    ]
    N = len(grid)
    M = len(grid[0])
    
    start_player = (0, 0)
    start_boss = (5, 5)
    target = (5, 5)
    
    # BFS
    # State: (px, py, bx, by)
    initial_state = (start_player[0], start_player[1], start_boss[0], start_boss[1])
    queue = collections.deque([(0, initial_state)])
    visited = set([initial_state])
    
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)] # Up, Down, Left, Right
    
    while queue:
        steps, (px, py, bx, by) = queue.popleft()
        
        if (px, py) == target:
            print(f"Minimum Steps: {steps}")
            return
        
        for dx, dy in moves:
            # Player move
            npx, npy = px + dx, py + dy
            # Boss move (Mirrored)
            nbx, nby = bx - dx, by - dy
            
            # Check bounds and walls for Player
            if 0 <= npx < N and 0 <= npy < M and grid[npx][npy] == 0:
                # Check bounds and walls for Boss
                if 0 <= nbx < N and 0 <= nby < M and grid[nbx][nby] == 0:
                    new_state = (npx, npy, nbx, nby)
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((steps + 1, new_state))
                        
    print("-1")

if __name__ == "__main__":
    solve()
