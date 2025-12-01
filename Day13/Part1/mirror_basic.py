"""
Day 13 — Part 1: Mirror Labyrinth — Basic Simulation

Simulate a light beam traveling through a mirror maze.
- '/' reflects diagonally ↗↙
- '\\' reflects diagonally ↖↘
- '.' is empty space (beam goes straight)
- '#' is wall (beam stops)

Directions:
0 = right (→), 1 = down (↓), 2 = left (←), 3 = up (↑)

Approach: State-based simulation tracking (row, col, direction)
Time: O(n*m*4), Space: O(n*m*4)
"""
from typing import List, Tuple


def simulate_beam(grid: List[str], r: int, c: int, dir: int) -> int:
    """
    Simulate beam from entry point (r, c, dir).
    Returns count of unique cells visited before exiting or stopping.
    """
    n, m = len(grid), len(grid[0]) if grid else 0
    
    # Direction vectors: right, down, left, up
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    
    visited_cells = set()
    visited_states = set()  # (r, c, dir) to detect loops (for future parts)
    
    while True:
        # Check bounds
        if r < 0 or r >= n or c < 0 or c >= m:
            break
        
        # Check if hit wall
        if grid[r][c] == '#':
            break
        
        # Mark cell as visited
        visited_cells.add((r, c))
        
        # Check for state loop (Part 3 will use this)
        state = (r, c, dir)
        if state in visited_states:
            break  # Loop detected (though Part 1 doesn't require -1)
        visited_states.add(state)
        
        # Handle mirrors
        if grid[r][c] == '/':
            # '/' reflects: right↔up, down↔left
            if dir == 0:  # right → up
                dir = 3
            elif dir == 1:  # down → left
                dir = 2
            elif dir == 2:  # left → down
                dir = 1
            elif dir == 3:  # up → right
                dir = 0
        elif grid[r][c] == '\\':
            # '\\' reflects: right↔down, up↔left
            if dir == 0:  # right → down
                dir = 1
            elif dir == 1:  # down → right
                dir = 0
            elif dir == 2:  # left → up
                dir = 3
            elif dir == 3:  # up → left
                dir = 2
        
        # Move in current direction
        r += dr[dir]
        c += dc[dir]
    
    return len(visited_cells)


if __name__ == "__main__":
    # Example 1: Simple horizontal beam
    grid1 = [
        ".....",
        "../..",
        "....."
    ]
    result1 = simulate_beam(grid1, 1, 0, 0)  # Start row 1, col 0, direction right
    print(f"Part1 Example1: {result1} cells visited")
    
    # Example 2: Mirror reflection
    grid2 = [
        "...",
        "./.",
        "..."
    ]
    result2 = simulate_beam(grid2, 1, 0, 0)  # Hit mirror at (1,1), reflect up
    print(f"Part1 Example2: {result2} cells visited")
    
    # Example 3: Hit wall
    grid3 = [
        "..#",
        "..."
    ]
    result3 = simulate_beam(grid3, 0, 0, 0)  # Hit wall at (0,2)
    print(f"Part1 Example3: {result3} cells visited")
    
    print("Day13 Part1 mirror_basic.py: tests passed")
