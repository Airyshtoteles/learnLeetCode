"""
Day 11 — Part 3: Hybrid Heuristic (A* with Portal Support)

A* algorithm for 3D labyrinth with portal teleportation.
Uses Manhattan distance as heuristic to guide search toward goal.

Approach:
1. Priority queue ordered by f(n) = g(n) + h(n)
   - g(n) = actual cost from start
   - h(n) = Manhattan distance to goal (admissible heuristic)
2. When at portal, consider teleportation to other portals.
3. A* guarantees optimal path when heuristic is admissible.

Time: O(n*m*h * log(n*m*h)) with priority queue
Space: O(n*m*h)
"""
from typing import List
import heapq


def manhattan_3d(z1: int, x1: int, y1: int, z2: int, x2: int, y2: int) -> int:
    """3D Manhattan distance heuristic."""
    return abs(z1 - z2) + abs(x1 - x2) + abs(y1 - y2)


def astar_3d_portal(n: int, m: int, h: int, k: int, grid: List[List[List[int]]]) -> int:
    """
    A* search in 3D with portal teleportation.
    Returns minimum cost or -1 if unreachable.
    """
    if grid[0][0][0] == 1 or grid[h-1][n-1][m-1] == 1:
        return -1
    
    goal = (h-1, n-1, m-1)
    
    # Collect portals
    portals = []
    for z in range(h):
        for x in range(n):
            for y in range(m):
                if grid[z][x][y] == 2:
                    portals.append((z, x, y))
    
    # Priority queue: (f_score, g_score, z, x, y)
    pq = [(manhattan_3d(0, 0, 0, *goal), 0, 0, 0, 0)]
    visited = {}  # (z,x,y) -> best g_score
    visited[(0, 0, 0)] = 0
    
    directions = [(1,0,0), (-1,0,0), (0,1,0), (0,-1,0), (0,0,1), (0,0,-1)]
    
    while pq:
        f, g, z, x, y = heapq.heappop(pq)
        
        # Check if reached goal
        if (z, x, y) == goal:
            return g
        
        # Skip if we've found a better path to this position
        if (z, x, y) in visited and visited[(z, x, y)] < g:
            continue
        
        # Normal movement
        for dz, dx, dy in directions:
            nz, nx, ny = z + dz, x + dx, y + dy
            
            if 0 <= nz < h and 0 <= nx < n and 0 <= ny < m and grid[nz][nx][ny] != 1:
                new_g = g + 1
                if (nz, nx, ny) not in visited or new_g < visited[(nz, nx, ny)]:
                    visited[(nz, nx, ny)] = new_g
                    new_f = new_g + manhattan_3d(nz, nx, ny, *goal)
                    heapq.heappush(pq, (new_f, new_g, nz, nx, ny))
        
        # Portal teleportation
        if grid[z][x][y] == 2:
            for pz, px, py in portals:
                new_g = g + k
                if (pz, px, py) not in visited or new_g < visited[(pz, px, py)]:
                    visited[(pz, px, py)] = new_g
                    new_f = new_g + manhattan_3d(pz, px, py, *goal)
                    heapq.heappush(pq, (new_f, new_g, pz, px, py))
    
    return -1


if __name__ == "__main__":
    # Example from problem
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
    result = astar_3d_portal(n, m, h, k, grid)
    print(f"Day11 Part3: A* result = {result} (expected ~6)")
    
    # Simple test
    grid2 = [
        [[0, 0], [0, 0]],
        [[0, 0], [0, 0]]
    ]
    result2 = astar_3d_portal(2, 2, 2, 1, grid2)
    assert result2 == 3, f"Expected 3, got {result2}"
    
    print("Day11 Part3 labyrinth_astar.py: tests passed")
