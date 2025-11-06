from collections import deque
from typing import List, Tuple

def min_steps_sliding_trap_maze(maze: List[List[str]]) -> int:
    m, n = len(maze), len(maze[0])
    start = end = None
    for r in range(m):
        for c in range(n):
            if maze[r][c] == 'S':
                start = (r, c)
            elif maze[r][c] == 'E':
                end = (r, c)
    if start is None or end is None:
        return -1

    def in_bounds(r: int, c: int) -> bool:
        return 0 <= r < m and 0 <= c < n

    # BFS state: (r, c, rowsMask, colsMask)
    sr, sc = start
    er, ec = end
    q = deque()
    q.append((sr, sc, 0, 0, 0))  # (r, c, rowsMask, colsMask, dist)
    visited = set()
    visited.add((sr, sc, 0, 0))

    while q:
        r, c, rm, cm, d = q.popleft()
        if (r, c) == (er, ec):
            return d

        # When leaving current cell, if current cell is a trap, block its row/col
        nrm, ncm = rm, cm
        if maze[r][c] == 'T':
            nrm = rm | (1 << r)
            ncm = cm | (1 << c)

        for dr, dc in ((1,0),(-1,0),(0,1),(0,-1)):
            nr, nc = r + dr, c + dc
            if not in_bounds(nr, nc):
                continue
            if maze[nr][nc] == '#':
                continue
            # Target cell must not be in a blocked row or column
            if (nrm >> nr) & 1:
                continue
            if (ncm >> nc) & 1:
                continue
            state = (nr, nc, nrm, ncm)
            if state in visited:
                continue
            visited.add(state)
            q.append((nr, nc, nrm, ncm, d + 1))

    return -1

if __name__ == "__main__":
    maze = [
      ['S','.','T','.'],
      ['.','.','.','.'],
      ['.','T','.','E']
    ]
    print(min_steps_sliding_trap_maze(maze))  # Expected 7
