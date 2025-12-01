from collections import deque

def solve_labyrinth(grid, K):
    N = len(grid)
    M = len(grid[0])
    
    # Queue: (r, c, time)
    queue = deque([(0, 0, 0)])
    
    # Visited: (r, c, time % K)
    visited = set([(0, 0, 0)])
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (0, 0)] # (0,0) is wait
    
    while queue:
        r, c, time = queue.popleft()
        
        if r == N - 1 and c == M - 1:
            return time
        
        next_time = time + 1
        mod_time = next_time % K
        
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < N and 0 <= nc < M:
                # Check if blocked
                # Blocked if (next_time + T[nr][nc]) % K == 0
                if (next_time + grid[nr][nc]) % K != 0:
                    if (nr, nc, mod_time) not in visited:
                        visited.add((nr, nc, mod_time))
                        queue.append((nr, nc, next_time))
                        
    return -1

if __name__ == "__main__":
    Grid = [
        [1, 2],
        [3, 4]
    ]
    K = 3
    result = solve_labyrinth(Grid, K)
    print(f"Minimum Time: {result}")
