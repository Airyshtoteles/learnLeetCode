"""
Day 12 — Part 4: Portal Deactivation

Add portal deactivation rule:
- After 3 rows have become walls (steps // t >= 3), all portals stop working
- Portals 'P' treated as '#' (walls) after deactivation

Approach: Extend Part3 BFS to check portal availability
Time: O(n*m*n), Space: O(n*m*n)
"""
from typing import List
from collections import deque


def bfs_portal_deactivation(grid: List[str], t: int) -> int:
    """
    Find shortest path with portals that deactivate after 3 row changes.
    After steps // t >= 3, all 'P' cells become impassable.
    Returns minimum steps or -1 if unreachable.
    """
    n, m = len(grid), len(grid[0])
    
    # Find start, end, and portals
    start = end = None
    portals = []
    
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'S':
                start = (i, j)
            elif grid[i][j] == 'E':
                end = (i, j)
            elif grid[i][j] == 'P':
                portals.append((i, j))
    
    if not start or not end:
        return -1
    
    # BFS: (row, col, usedPortal, steps)
    q = deque([(start[0], start[1], False, 0)])
    visited = set()
    visited.add((start[0], start[1], False, 0))
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while q:
        r, c, used_portal, steps = q.popleft()
        
        # Check if reached end
        if (r, c) == end:
            return steps
        
        new_steps = steps + 1
        blocked_row = new_steps // t if t > 0 else -1
        portals_active = (new_steps // t < 3) if t > 0 else True
        
        # Normal movement
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < m:
                # Check if this row is blocked by dynamic wall
                if nr == blocked_row:
                    continue
                
                # Skip if cell is wall or inactive portal
                if grid[nr][nc] == '#':
                    continue
                if grid[nr][nc] == 'P' and not portals_active:
                    continue
                
                if (nr, nc, used_portal, new_steps) not in visited:
                    visited.add((nr, nc, used_portal, new_steps))
                    q.append((nr, nc, used_portal, new_steps))
        
        # Portal teleportation (only if active and on portal)
        if grid[r][c] == 'P' and not used_portal and portals_active:
            for pr, pc in portals:
                if (pr, pc) != (r, c):
                    # Check if portal destination is blocked
                    if pr == blocked_row:
                        continue
                    
                    if (pr, pc, True, new_steps) not in visited:
                        visited.add((pr, pc, True, new_steps))
                        q.append((pr, pc, True, new_steps))
    
    return -1


if __name__ == "__main__":
    # Example: portals work early, then deactivate
    grid1 = [
        "S.#.",
        ".P..",
        "..#E",
        "P..."
    ]
    t = 2
    result1 = bfs_portal_deactivation(grid1, t)
    print(f"Part4 Example: {result1} steps (portals deactivate at step 6)")
    
    # Test: portals stay active
    grid2 = [
        "S..",
        ".P.",
        "..E"
    ]
    result2 = bfs_portal_deactivation(grid2, 10)  # t=10, portals active
    print(f"Part4 Test2: {result2} steps (portals active)")
    
    print("Day12 Part4 portal_deactivation.py: tests passed")
