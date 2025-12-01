"""
Day 12 — Part 1: Dynamic Walls and Magic Portals (Basic BFS)

Find shortest path from 'S' to 'E' in a 2D grid.
- '.' = passable
- '#' = wall
- 'S' = start
- 'E' = end
- 'P' = portal (ignored in Part 1)

Approach: Standard BFS
Time: O(n*m), Space: O(n*m)
"""
from typing import List
from collections import deque


def bfs_basic(grid: List[str]) -> int:
    """
    Find shortest path from S to E using basic BFS.
    Returns minimum steps or -1 if unreachable.
    """
    n, m = len(grid), len(grid[0])
    
    # Find start and end positions
    start = end = None
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'S':
                start = (i, j)
            elif grid[i][j] == 'E':
                end = (i, j)
    
    if not start or not end:
        return -1
    
    # BFS
    q = deque([(start[0], start[1], 0)])  # (row, col, steps)
    visited = set()
    visited.add(start)
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while q:
        r, c, steps = q.popleft()
        
        # Check if reached end
        if (r, c) == end:
            return steps
        
        # Explore neighbors
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < m and (nr, nc) not in visited:
                if grid[nr][nc] != '#':  # Can pass through '.', 'P', 'E'
                    visited.add((nr, nc))
                    q.append((nr, nc, steps + 1))
    
    return -1


if __name__ == "__main__":
    # Example from problem
    grid1 = [
        "S.#.",
        ".P..",
        "..#E",
        "P..."
    ]
    result1 = bfs_basic(grid1)
    print(f"Part1 Example: {result1} steps")
    assert result1 > 0, f"Should find a path, got {result1}"
    
    # Simple test
    grid2 = [
        "S.E"
    ]
    result2 = bfs_basic(grid2)
    assert result2 == 2, f"Expected 2, got {result2}"
    
    # Blocked test
    grid3 = [
        "S#E"
    ]
    result3 = bfs_basic(grid3)
    assert result3 == -1, f"Expected -1, got {result3}"
    
    print("Day12 Part1 magic_portals.py: all tests passed")
