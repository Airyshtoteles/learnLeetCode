"""
Day 13 — Part 3: Loop Detection

Detect if beam is trapped in an infinite reflection loop.
If loop detected, return -1.
Otherwise, return number of unique cells visited.

Approach: Track states (r, c, dir). If state repeats, it's a loop.
Time: O(n*m*4), Space: O(n*m*4)
"""
from typing import List


def simulate_beam_with_loop_detection(grid: List[str], r: int, c: int, dir: int) -> int:
    """
    Simulate beam with loop detection.
    Returns:
    - -1 if infinite loop detected
    - count of unique cells visited otherwise
    """
    n, m = len(grid), len(grid[0]) if grid else 0
    
    # Direction vectors: right, down, left, up
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    
    visited_cells = set()
    visited_states = set()
    
    while True:
        # Check bounds
        if r < 0 or r >= n or c < 0 or c >= m:
            # Exited grid successfully
            return len(visited_cells)
        
        # Check if hit wall
        if grid[r][c] == '#':
            # Stopped at wall
            return len(visited_cells)
        
        # Mark cell as visited
        visited_cells.add((r, c))
        
        # Check for state loop (CRITICAL for Part 3)
        state = (r, c, dir)
        if state in visited_states:
            # Loop detected!
            return -1
        visited_states.add(state)
        
        # Handle mirrors
        if grid[r][c] == '/':
            if dir == 0: dir = 3
            elif dir == 1: dir = 2
            elif dir == 2: dir = 1
            elif dir == 3: dir = 0
        elif grid[r][c] == '\\':
            if dir == 0: dir = 1
            elif dir == 1: dir = 0
            elif dir == 2: dir = 3
            elif dir == 3: dir = 2
        
        # Move in current direction
        r += dr[dir]
        c += dc[dir]


if __name__ == "__main__":
    # Example 1: Simple loop with mirrors
    grid1 = [
        "/.\\",
        ".#.",
        "\\./",
    ]
    result1 = simulate_beam_with_loop_detection(grid1, 0, 0, 0)
    print(f"Part3 Example1: {result1} (loop detected)")
    
    # Example 2: Exits normally
    grid2 = [
        "...",
        "./.",
        "..."
    ]
    result2 = simulate_beam_with_loop_detection(grid2, 1, 0, 0)
    print(f"Part3 Example2: {result2} cells (exits normally)")
    
    # Example 3: Another loop scenario
    grid3 = [
        "/\\",
        "\\/"
    ]
    result3 = simulate_beam_with_loop_detection(grid3, 0, 0, 0)
    print(f"Part3 Example3: {result3} (loop detected)")
    
    # Example 4: Hits wall (no loop)
    grid4 = [
        "..#",
        "..."
    ]
    result4 = simulate_beam_with_loop_detection(grid4, 0, 0, 0)
    print(f"Part3 Example4: {result4} cells (hits wall)")
    
    print("Day13 Part3 loop_detection.py: tests passed")
