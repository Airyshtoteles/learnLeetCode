from collections import deque
from typing import List

def count_heard_cells(grid: List[List[int]]) -> int:
    if not grid:
        return 0
    m, n = len(grid), len(grid[0])
    
    # Queue: (r, c, bounced_flag)
    q = deque()
    visited = set()
    heard = set()
    
    # Initialize sources
    for r in range(m):
        for c in range(n):
            if grid[r][c] == 2:
                q.append((r, c, 0))
                visited.add((r, c, 0))
                heard.add((r, c))
    
    dirs = [(0,1), (0,-1), (1,0), (-1,0)] # R, L, D, U
    
    while q:
        r, c, bounced = q.popleft()
        
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < m and 0 <= nc < n:
                if grid[nr][nc] == 1:
                    # Hit wall
                    if not bounced:
                        # Bounce back: from wall (nr,nc) back to (r,c) is effectively
                        # starting a new wave from (r,c) in direction (-dr, -dc)?
                        # Or simply the wave is now at (r,c) ready to move opposite?
                        # Problem: "bounced back in opposite direction in next second".
                        # So at t+1, it is at (r + (-dr), c + (-dc))?
                        # Let's assume it reflects: effectively moving from (r,c) to (r-dr, c-dc) is the bounce step.
                        
                        # Actually, simpler: The wave at (r,c) tried to go to (nr,nc).
                        # It hit wall. Next step, it travels from (r,c) to (r-dr, c-dc).
                        br, bc = r - dr, c - dc
                        if 0 <= br < m and 0 <= bc < n and grid[br][bc] != 1:
                            if (br, bc, 1) not in visited:
                                visited.add((br, bc, 1))
                                heard.add((br, bc))
                                q.append((br, bc, 1))
                else:
                    # Normal spread
                    if (nr, nc, bounced) not in visited:
                        visited.add((nr, nc, bounced))
                        heard.add((nr, nc))
                        q.append((nr, nc, bounced))
                        
    return len(heard)

if __name__ == "__main__":
    grid = [
      [0,1,0,0],
      [2,1,0,1],
      [0,0,0,0]
    ]
    print(count_heard_cells(grid))
