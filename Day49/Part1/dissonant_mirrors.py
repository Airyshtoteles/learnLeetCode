from collections import deque

def solve_dissonant_mirrors(n, m, grid):
    # BFS State: (r, c, grid_state)
    # grid_state: 0 = Normal, 1 = Inverted
    
    queue = deque([(0, 0, 0, 0)]) # r, c, state, steps
    visited = set([(0, 0, 0)])
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while queue:
        r, c, state, steps = queue.popleft()
        
        if r == n - 1 and c == m - 1:
            return steps
        
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < m:
                # Determine value of next cell in current state
                cell_val = grid[nr][nc] ^ state
                
                new_state = state
                if cell_val == 1:
                    new_state = 1 - state
                    
                if (nr, nc, new_state) not in visited:
                    visited.add((nr, nc, new_state))
                    queue.append((nr, nc, new_state, steps + 1))
                    
    return -1

if __name__ == "__main__":
    Grid = [
        [0, 1],
        [1, 0]
    ]
    N = len(Grid)
    M = len(Grid[0])
    
    result = solve_dissonant_mirrors(N, M, Grid)
    print(f"Minimum Steps: {result}")
