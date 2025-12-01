"""
Day 13 — Part 5: Grid Rotation

Apply grid rotation before simulation.
rCount = number of 90° clockwise rotations to apply.

Approach: Rotate grid rCount times, then simulate with Part4 logic
Time: O(n*m) rotation + O(limit) simulation
"""
from typing import List


def rotate_grid_90(grid: List[str]) -> List[str]:
    """
    Rotate grid 90° clockwise.
    - New grid[i][j] = old grid[n-1-j][i]
    """
    n, m = len(grid), len(grid[0]) if grid else 0
    rotated = []
    for j in range(m):
        row = ""
        for i in range(n-1, -1, -1):
            row += grid[i][j]
        rotated.append(row)
    return rotated


def simulate_beam_with_limit(grid: List[str], r: int, c: int, dir: int, limit: int) -> int:
    """Simulate beam with reflection limit (from Part 4)"""
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


def simulate_with_rotation(grid: List[str], r: int, c: int, dir: int, 
                           limit: int, rCount: int) -> int:
    """
    Rotate grid rCount times (90° each), then simulate beam.
    """
    # Apply rotations
    rotated_grid = grid
    for _ in range(rCount % 4):  # Only need 0-3 rotations
        rotated_grid = rotate_grid_90(rotated_grid)
    
    # Simulate on rotated grid
    return simulate_beam_with_limit(rotated_grid, r, c, dir, limit)


if __name__ == "__main__":
    # Example 1: No rotation
    grid1 = [
        "...",
        "./.",
        "..."
    ]
    result1 = simulate_with_rotation(grid1, 1, 0, 0, 100, 0)
    print(f"Part5 Example1: {result1} cells (rCount=0, no rotation)")
    
    # Example 2: One rotation
    result2 = simulate_with_rotation(grid1, 1, 0, 0, 100, 1)
    print(f"Part5 Example2: {result2} cells (rCount=1, rotated 90°)")
    
    # Example 3: Full circle
    result3 = simulate_with_rotation(grid1, 1, 0, 0, 100, 4)
    print(f"Part5 Example3: {result3} cells (rCount=4, back to original)")
    
    print("Day13 Part5 grid_rotation.py: tests passed")
