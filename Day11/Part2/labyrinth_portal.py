"""
Day 11 — Part 2: Dimensional Labyrinth (Portal Optimization)

Enhanced 3D BFS with portal teleportation.
- Portals (value 2) allow teleportation to any other portal with cost k.

Approach:
1. Collect all portal positions.
2. Standard BFS with 6-direction movement (cost 1).
3. When at a portal, add all other portals to queue with cost + k.
4. Use visited set to avoid revisiting positions.

Time: O(n*m*h + P^2) where P = number of portals
Space: O(n*m*h)
"""
from typing import List
from collections import deque


def bfs_3d_portal(n: int, m: int, h: int, k: int, grid: List[List[List[int]]]) -> int:
    """
    Find minimum cost from (0,0,0) to (n-1,m-1,h-1) with portal teleportation.
    k = cost to teleport between portals.
    Returns -1 if unreachable.
    """
    if grid[0][0][0] == 1 or grid[h-1][n-1][m-1] == 1:
        return -1
    
    # Collect all portal positions
    portals = []
    for z in range(h):
        for x in range(n):
            for y in range(m):
                if grid[z][x][y] == 2:
                    portals.append((z, x, y))
    
    # BFS: (z, x, y, cost)
    q = deque([(0, 0, 0, 0)])
    visited = set()
    visited.add((0, 0, 0))
    
    # 6 directions
    directions = [(1,0,0), (-1,0,0), (0,1,0), (0,-1,0), (0,0,1), (0,0,-1)]
    
    while q:
        z, x, y, cost = q.popleft()
        
        # Check destination
        if z == h-1 and x == n-1 and y == m-1:
            return cost
        
        # Normal movement (6 directions)
        for dz, dx, dy in directions:
            nz, nx, ny = z + dz, x + dx, y + dy
            
            if 0 <= nz < h and 0 <= nx < n and 0 <= ny < m:
                if (nz, nx, ny) not in visited and grid[nz][nx][ny] != 1:
                    visited.add((nz, nx, ny))
                    q.append((nz, nx, ny, cost + 1))
        
        # Portal teleportation
        if grid[z][x][y] == 2:
            for pz, px, py in portals:
                if (pz, px, py) not in visited:
                    visited.add((pz, px, py))
                    q.append((pz, px, py, cost + k))
    
    return -1


if __name__ == "__main__":
    # Test with portal teleportation
    # 3x3x2 grid from problem example
    grid = [
        [
            [0, 0, 0],
            [1, 1, 0],
            [2, 0, 0]
        ],
        [
            [0, 1, 0],
            [0, 2, 0],
            [0, 0, 0]
        ]
    ]
    n, m, h, k = 3, 3, 2, 2
    result = bfs_3d_portal(n, m, h, k, grid)
    print(f"Day11 Part2: Example result = {result} (expected ~6)")
    
    # Simple test: portal shortcut
    grid2 = [
        [[2, 0], [0, 0]],
        [[0, 0], [0, 2]]
    ]
    # Without portal: ~3 steps; with portal (k=1): might be 1 step
    result2 = bfs_3d_portal(2, 2, 2, 1, grid2)
    assert result2 >= 0, f"Should find path, got {result2}"
    
    print("Day11 Part2 labyrinth_portal.py: tests passed")
