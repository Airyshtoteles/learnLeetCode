"""
Day 12 — Part 5: Optimization for Large Grids

Handle large grids (n, m ≤ 500) efficiently using A* pathfinding.

Approach: A* with Manhattan distance heuristic
Priority: f(state) = g(steps) + h(manhattan to end)
Time: O(n*m*log(n*m)), Space: O(n*m)
"""
from typing import List
import heapq


def astar_optimized(grid: List[str], t: int) -> int:
    """
    Find shortest path using A* with Manhattan heuristic.
    Handles dynamic walls and portal deactivation efficiently.
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
    
    def manhattan(r1, c1, r2, c2):
        return abs(r1 - r2) + abs(c1 - c2)
    
    # A* priority queue: (f_score, steps, row, col, usedPortal)
    h_start = manhattan(start[0], start[1], end[0], end[1])
    pq = [(h_start, 0, start[0], start[1], False)]
    visited = set()
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while pq:
        f_score, steps, r, c, used_portal = heapq.heappop(pq)
        
        # Skip if already visited this state
        if (r, c, used_portal) in visited:
            continue
        visited.add((r, c, used_portal))
        
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
                if nr == blocked_row:
                    continue
                
                if grid[nr][nc] == '#':
                    continue
                if grid[nr][nc] == 'P' and not portals_active:
                    continue
                
                if (nr, nc, used_portal) not in visited:
                    h = manhattan(nr, nc, end[0], end[1])
                    f = new_steps + h
                    heapq.heappush(pq, (f, new_steps, nr, nc, used_portal))
        
        # Portal teleportation
        if grid[r][c] == 'P' and not used_portal and portals_active:
            for pr, pc in portals:
                if (pr, pc) != (r, c) and pr != blocked_row:
                    if (pr, pc, True) not in visited:
                        h = manhattan(pr, pc, end[0], end[1])
                        f = new_steps + h
                        heapq.heappush(pq, (f, new_steps, pr, pc, True))
    
    return -1


if __name__ == "__main__":
    # Example: same as Part4 but optimized
    grid1 = [
        "S.#.",
        ".P..",
        "..#E",
        "P..."
    ]
    t = 2
    result1 = astar_optimized(grid1, t)
    print(f"Part5 Example: {result1} steps (A* optimized)")
    
    # Test without dynamic walls interfering
    grid2 = [
        "S..",
        "...",
        "..E"
    ]
    result2 = astar_optimized(grid2, 1000)  # t=1000, very slow blocking
    print(f"Part5 Test2: {result2} steps (no blocking)")
    assert result2 == 4, f"Expected 4, got {result2}"  # Manhattan: 2 down + 2 right = 4
    
    print("Day12 Part5 optimized.py: tests passed")
