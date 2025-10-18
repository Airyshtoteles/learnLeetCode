"""
Day 12 — Part 2: Portal Teleportation (BFS with State)

Add portal mechanics:
- 'P' cells allow one-time teleportation to any other 'P'
- Use BFS with state: (row, col, usedPortal)

Approach: BFS with extended state
Time: O(n*m * 2), Space: O(n*m * 2)
"""
from typing import List
from collections import deque


def bfs_with_portal(grid: List[str]) -> int:
    """
    Find shortest path with one-time portal teleportation.
    Returns minimum steps or -1 if unreachable.
    """
    n, m = len(grid), len(grid[0])
    
    # Find start, end, and all portals
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
    
    # BFS with state: (row, col, usedPortal, steps)
    q = deque([(start[0], start[1], False, 0)])
    visited = set()
    visited.add((start[0], start[1], False))
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while q:
        r, c, used_portal, steps = q.popleft()
        
        # Check if reached end
        if (r, c) == end:
            return steps
        
        # Normal movement
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < m and (nr, nc, used_portal) not in visited:
                if grid[nr][nc] != '#':
                    visited.add((nr, nc, used_portal))
                    q.append((nr, nc, used_portal, steps + 1))
        
        # Portal teleportation (if standing on portal and haven't used it)
        if grid[r][c] == 'P' and not used_portal:
            for pr, pc in portals:
                if (pr, pc) != (r, c) and (pr, pc, True) not in visited:
                    visited.add((pr, pc, True))
                    q.append((pr, pc, True, steps + 1))
    
    return -1


if __name__ == "__main__":
    # Example from problem
    grid1 = [
        "S.#.",
        ".P..",
        "..#E",
        "P..."
    ]
    result1 = bfs_with_portal(grid1)
    print(f"Part2 Example: {result1} steps (with portal)")
    assert result1 > 0, f"Should find a path, got {result1}"
    
    # Test with beneficial portal use
    grid2 = [
        "S.....",
        "......",
        "P....P",
        "......",
        "......E"
    ]
    result2 = bfs_with_portal(grid2)
    print(f"Part2 Test2: {result2} steps")
    
    print("Day12 Part2 portal_bfs.py: tests passed")
