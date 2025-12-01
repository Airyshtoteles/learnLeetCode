"""
Day 11 — Part 1: Dimensional Labyrinth (3D BFS Basic)

Given a 3D grid (n x m x h), find minimum cost from (0,0,0) to (n-1,m-1,h-1).
- 0 = empty
- 1 = wall
- 2 = portal (ignored in Part 1)

Movement: 6 directions (+/- x, y, z), each step costs 1.

Approach: Standard BFS in 3D space.
Time: O(n * m * h), Space: O(n * m * h)
"""
from typing import List
from collections import deque


def bfs_3d_basic(n: int, m: int, h: int, grid: List[List[List[int]]]) -> int:
    """
    Find minimum steps from (0,0,0) to (n-1,m-1,h-1) in 3D grid.
    Returns -1 if unreachable.
    """
    if grid[0][0][0] == 1 or grid[h-1][n-1][m-1] == 1:
        return -1
    
    # BFS: (z, x, y, cost)
    q = deque([(0, 0, 0, 0)])
    visited = set()
    visited.add((0, 0, 0))
    
    # 6 directions in 3D
    directions = [(1,0,0), (-1,0,0), (0,1,0), (0,-1,0), (0,0,1), (0,0,-1)]
    
    while q:
        z, x, y, cost = q.popleft()
        
        # Check if reached destination
        if z == h-1 and x == n-1 and y == m-1:
            return cost
        
        # Explore neighbors
        for dz, dx, dy in directions:
            nz, nx, ny = z + dz, x + dx, y + dy
            
            # Bounds check
            if 0 <= nz < h and 0 <= nx < n and 0 <= ny < m:
                if (nz, nx, ny) not in visited and grid[nz][nx][ny] != 1:
                    visited.add((nz, nx, ny))
                    q.append((nz, nx, ny, cost + 1))
    
    return -1


if __name__ == "__main__":
    # Simple test: 2x2x2 cube, straight path
    grid1 = [
        [[0, 0], [0, 0]],
        [[0, 0], [0, 0]]
    ]
    # Path: (0,0,0) -> (0,1,0) -> (0,1,1) -> (1,1,1) = 3 steps
    result1 = bfs_3d_basic(2, 2, 2, grid1)
    assert result1 == 3, f"Expected 3, got {result1}"
    
    # Test with wall
    grid2 = [
        [[0, 0], [1, 0]],
        [[0, 0], [0, 0]]
    ]
    result2 = bfs_3d_basic(2, 2, 2, grid2)
    assert result2 > 0, f"Should find a path, got {result2}"
    
    # Test impossible
    grid3 = [
        [[0, 1], [1, 0]],
        [[1, 0], [0, 1]]
    ]
    result3 = bfs_3d_basic(2, 2, 2, grid3)
    assert result3 == -1, f"Should be unreachable, got {result3}"
    
    print("Day11 Part1 labyrinth_3d.py: all tests passed")
