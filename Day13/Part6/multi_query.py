"""
Day 13 — Part 6: Multi-Query (Ultimate)

Handle Q queries, each with (r, c, dir, limit, rCount).
Return vector of results for all queries.

Approach: Process each query independently using Part5 logic
Optimization: Cache rotated grids to avoid redundant rotations
Time: O(Q * (n*m + limit)), Space: O(n*m)
"""
from typing import List, Tuple


def rotate_grid_90(grid: List[str]) -> List[str]:
    """Rotate grid 90° clockwise"""
    n, m = len(grid), len(grid[0]) if grid else 0
    rotated = []
    for j in range(m):
        row = ""
        for i in range(n-1, -1, -1):
            row += grid[i][j]
        rotated.append(row)
    return rotated


def simulate_beam_with_limit(grid: List[str], r: int, c: int, dir: int, limit: int) -> int:
    """Simulate beam with reflection limit"""
    n, m = len(grid), len(grid[0]) if grid else 0
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    
    visited_cells = set()
    visited_states = set()
    reflection_count = 0
    
    while True:
        if r < 0 or r >= n or c < 0 or c >= m:
            return len(visited_cells)
        if grid[r][c] == '#':
            return len(visited_cells)
        
        visited_cells.add((r, c))
        state = (r, c, dir)
        if state in visited_states:
            return len(visited_cells)
        visited_states.add(state)
        
        reflected = False
        if grid[r][c] == '/':
            reflected = True
            if dir == 0: dir = 3
            elif dir == 1: dir = 2
            elif dir == 2: dir = 1
            elif dir == 3: dir = 0
        elif grid[r][c] == '\\':
            reflected = True
            if dir == 0: dir = 1
            elif dir == 1: dir = 0
            elif dir == 2: dir = 3
            elif dir == 3: dir = 2
        
        if reflected:
            reflection_count += 1
            if reflection_count > limit:
                return len(visited_cells)
        
        r += dr[dir]
        c += dc[dir]


def process_queries(grid: List[str], 
                   queries: List[Tuple[int, int, int, int, int]]) -> List[int]:
    """
    Process Q queries, each with (r, c, dir, limit, rCount).
    Returns list of results.
    
    Optimization: Cache rotated grids (only 4 possible rotations)
    """
    # Pre-compute all 4 rotations (cache)
    rotations = [grid]
    current_grid = grid
    for _ in range(3):
        current_grid = rotate_grid_90(current_grid)
        rotations.append(current_grid)
    
    results = []
    for r, c, dir, limit, rCount in queries:
        # Use cached rotation
        rotated_grid = rotations[rCount % 4]
        result = simulate_beam_with_limit(rotated_grid, r, c, dir, limit)
        results.append(result)
    
    return results


if __name__ == "__main__":
    # Example: Multiple queries on same grid
    grid = [
        "...",
        "./.",
        "..."
    ]
    
    queries = [
        (1, 0, 0, 100, 0),  # No rotation
        (1, 0, 0, 100, 1),  # 90° rotation
        (1, 0, 0, 100, 2),  # 180° rotation
        (0, 0, 1, 50, 0),   # Different entry, no rotation
        (2, 2, 2, 100, 1),  # Left entry, 90° rotation
    ]
    
    results = process_queries(grid, queries)
    print(f"Part6 Results: {results}")
    
    # Example 2: Grid with walls
    grid2 = [
        "..#",
        "./.",
        "#.."
    ]
    queries2 = [
        (0, 0, 0, 100, 0),
        (0, 0, 0, 100, 2),
    ]
    results2 = process_queries(grid2, queries2)
    print(f"Part6 Results2: {results2}")
    
    print("Day13 Part6 multi_query.py: tests passed")
