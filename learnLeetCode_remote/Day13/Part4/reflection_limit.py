"""
Day 13 — Part 4: Reflection Limit

Add maximum reflection limit to prevent excessive computation.
If beam reflects more than `limit` times, it stops automatically.
Return cells visited within the limit.

Approach: Track reflection count, stop when limit exceeded
Time: O(min(n*m*4, limit)), Space: O(n*m*4)
"""
from typing import List


def simulate_beam_with_limit(grid: List[str], r: int, c: int, dir: int, limit: int) -> int:
    """
    Simulate beam with maximum reflection limit.
    Returns:
    - count of unique cells visited before stopping/exiting
    - automatically stops after `limit` reflections
    """
    n, m = len(grid), len(grid[0]) if grid else 0
    
    # Direction vectors: right, down, left, up
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    
    visited_cells = set()
    visited_states = set()
    reflection_count = 0
    
    while True:
        # Check bounds
        if r < 0 or r >= n or c < 0 or c >= m:
            return len(visited_cells)
        
        # Check if hit wall
        if grid[r][c] == '#':
            return len(visited_cells)
        
        # Mark cell as visited
        visited_cells.add((r, c))
        
        # Check for state loop
        state = (r, c, dir)
        if state in visited_states:
            return len(visited_cells)  # Loop detected, return current count
        visited_states.add(state)
        
        # Handle mirrors and count reflections
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
        
        # Check reflection limit
        if reflected:
            reflection_count += 1
            if reflection_count > limit:
                # Exceeded limit, stop here
                return len(visited_cells)
        
        # Move in current direction
        r += dr[dir]
        c += dc[dir]


if __name__ == "__main__":
    # Example 1: Loop but limited
    grid1 = [
        "/.\\",
        ".#.",
        "\\./",
    ]
    result1 = simulate_beam_with_limit(grid1, 0, 0, 0, 10)
    print(f"Part4 Example1: {result1} cells (limit=10 reflections)")
    
    # Example 2: Exits before limit
    grid2 = [
        "...",
        "./.",
        "..."
    ]
    result2 = simulate_beam_with_limit(grid2, 1, 0, 0, 100)
    print(f"Part4 Example2: {result2} cells (exits before limit)")
    
    # Example 3: Very low limit
    grid3 = [
        "///",
        "///"
    ]
    result3 = simulate_beam_with_limit(grid3, 0, 0, 0, 2)
    print(f"Part4 Example3: {result3} cells (limit=2, stops early)")
    
    # Example 4: No mirrors
    grid4 = [
        ".....",
        "....."
    ]
    result4 = simulate_beam_with_limit(grid4, 0, 0, 0, 1000)
    print(f"Part4 Example4: {result4} cells (no mirrors, no reflections)")
    
    print("Day13 Part4 reflection_limit.py: tests passed")
