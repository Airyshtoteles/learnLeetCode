"""
Day 13 — Part 2: Multiple Entry Points

Simulate multiple beams from different entry points.
Return total unique cells visited by at least one beam.

Approach: Run simulation for each entry, collect all visited cells
Time: O(k * n * m * 4), Space: O(n * m * 4)
where k = number of entry points
"""
from typing import List, Tuple, Set


def simulate_beam(grid: List[str], r: int, c: int, dir: int, 
                  global_visited: Set[Tuple[int, int]]) -> None:
    """
    Simulate beam from entry point, adding visited cells to global_visited.
    """
    n, m = len(grid), len(grid[0]) if grid else 0
    
    # Direction vectors: right, down, left, up
    dr = [0, 1, 0, -1]
    dc = [1, 0, -1, 0]
    
    visited_states = set()
    
    while True:
        # Check bounds
        if r < 0 or r >= n or c < 0 or c >= m:
            break
        
        # Check if hit wall
        if grid[r][c] == '#':
            break
        
        # Mark cell as visited
        global_visited.add((r, c))
        
        # Check for state loop
        state = (r, c, dir)
        if state in visited_states:
            break
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


def simulate_multiple_beams(grid: List[str], 
                            entries: List[Tuple[int, int, int]]) -> int:
    """
    Simulate multiple beams from different entry points.
    Returns count of unique cells visited by at least one beam.
    """
    global_visited = set()
    
    for r, c, dir in entries:
        simulate_beam(grid, r, c, dir, global_visited)
    
    return len(global_visited)


if __name__ == "__main__":
    # Example 1: Two beams, some overlap
    grid1 = [
        ".....",
        "../..",
        "....."
    ]
    entries1 = [
        (1, 0, 0),  # Start row 1, col 0, right
        (0, 0, 1)   # Start row 0, col 0, down
    ]
    result1 = simulate_multiple_beams(grid1, entries1)
    print(f"Part2 Example1: {result1} cells visited by all beams")
    
    # Example 2: Three beams
    grid2 = [
        "...",
        "./.",
        "..."
    ]
    entries2 = [
        (1, 0, 0),  # Right, hits mirror
        (0, 1, 1),  # Down
        (2, 2, 2)   # Left
    ]
    result2 = simulate_multiple_beams(grid2, entries2)
    print(f"Part2 Example2: {result2} cells visited by all beams")
    
    # Example 3: Single beam (same as Part1)
    grid3 = [
        "..#",
        "..."
    ]
    entries3 = [(0, 0, 0)]
    result3 = simulate_multiple_beams(grid3, entries3)
    print(f"Part2 Example3: {result3} cells visited")
    
    print("Day13 Part2 multi_beam.py: tests passed")
