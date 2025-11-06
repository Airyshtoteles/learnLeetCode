from functools import lru_cache
from typing import List, Tuple

def serialize(grid: List[List[int]]) -> Tuple[Tuple[int,...], ...]:
    return tuple(tuple(row) for row in grid)

def gravity_down(col: List[int]) -> List[int]:
    # col is top..bottom; gravity packs non-zeros at bottom
    n = len(col)
    vals = [v for v in col if v != 0]
    zeros = [0]*(n - len(vals))
    return zeros + vals

def explode_column(col: List[int]) -> Tuple[List[int], int, bool]:
    # return new col after one explosion pass, destroyed count, whether any exploded
    n = len(col)
    to_zero = [False]*n
    i = 0
    destroyed = 0
    while i < n:
        j = i
        while j < n and col[j] == col[i] and col[i] != 0:
            j += 1
        run_len = j - i
        if col[i] != 0 and run_len >= 3:
            for t in range(i, j):
                to_zero[t] = True
            destroyed += run_len
        i = j if j > i else i + 1
    new_col = [0 if to_zero[r] else col[r] for r in range(n)]
    return new_col, destroyed, any(to_zero)

def simulate_column(grid: List[List[int]], c: int) -> Tuple[List[List[int]], int]:
    # Operate only on column c: apply gravity, explode, repeat until stable
    n = len(grid)
    col = [grid[r][c] for r in range(n)]
    total_destroyed = 0
    changed = True
    while changed:
        col = gravity_down(col)
        col, destroyed, exploded = explode_column(col)
        total_destroyed += destroyed
        changed = exploded and destroyed > 0
    # write back
    new_grid = [row[:] for row in grid]
    for r in range(n):
        new_grid[r][c] = col[r]
    return new_grid, total_destroyed

@lru_cache(maxsize=None)
def dfs(state: Tuple[Tuple[int,...], ...], moves: int) -> int:
    if moves == 0:
        return 0
    grid = [list(row) for row in state]
    n = len(grid)
    best = 0
    for c in range(n):
        next_grid, destroyed = simulate_column(grid, c)
        gain = destroyed + dfs(serialize(next_grid), moves - 1)
        if gain > best:
            best = gain
    return best

if __name__ == "__main__":
    grid = [
      [1,2,1],
      [2,1,2],
      [1,2,1]
    ]
    k = 3
    print(dfs(serialize(grid), k))  # Example target: 6
