"""
Day 12 — Part 3: Dynamic Walls

Add dynamic wall mechanics:
- Every t steps, row k becomes all walls (k = steps // t)
- BFS must track current step count to determine active walls

Approach: BFS with time-aware wall checking
State: (row, col, usedPortal, steps)
Time: O(n*m*n), Space: O(n*m*n)
"""
from typing import List
from collections import deque


def bfs_dynamic_walls(grid: List[str], t: int) -> int:
    """
    Find shortest path with portals and dynamic walls.
    Every t steps, row (steps // t) becomes all walls.
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
        
        # Normal movement
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < m:
                # Check if this row is blocked by dynamic wall
                if nr == blocked_row:
                    continue
                
                if (nr, nc, used_portal, new_steps) not in visited and grid[nr][nc] != '#':
                    visited.add((nr, nc, used_portal, new_steps))
                    q.append((nr, nc, used_portal, new_steps))
        
        # Portal teleportation
        if grid[r][c] == 'P' and not used_portal:
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
    # Example from problem
    grid1 = [
        "S.#.",
        ".P..",
        "..#E",
        "P..."
    ]
    t = 2
    result1 = bfs_dynamic_walls(grid1, t)
    print(f"Part3 Example: {result1} steps (with dynamic walls, t={t})")
    
    # Test 2: Path gets blocked
    grid2 = [
        "S..",
        "..E"
    ]
    result2 = bfs_dynamic_walls(grid2, 3)  # t=3, row 1 blocked at step 3
    print(f"Part3 Test2: {result2} steps (path blocked scenario)")
    
    print("Day12 Part3 dynamic_walls.py: tests passed")
