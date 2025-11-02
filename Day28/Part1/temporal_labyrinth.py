from collections import deque
from math import gcd
from typing import List, Tuple

def lcm(a: int, b: int) -> int:
    return a // gcd(a,b) * b if a and b else a or b

def min_time(grid: List[str]) -> int:
    n = len(grid)
    m = len(grid[0]) if n else 0
    if n == 0 or m == 0:
        return -1
    start = end = None
    portals = {str(d): [] for d in range(10)}
    L = 1
    for i in range(n):
        for j in range(m):
            c = grid[i][j]
            if c == 'S':
                start = (i, j)
            elif c == 'E':
                end = (i, j)
            elif c.isdigit():
                portals[c].append((i, j))
                if c != '0':
                    L = lcm(L, int(c))
    if start is None or end is None:
        return -1
    if L == 0:
        L = 1
    DIRS = [(-1,0),(1,0),(0,-1),(0,1),(0,0)]  # include wait
    vis = [[[False]*L for _ in range(m)] for __ in range(n)]
    q = deque([(start[0], start[1], 0)])
    vis[start[0]][start[1]][0] = True

    def is_wall(i: int, j: int) -> bool:
        return grid[i][j] == 'W'

    while q:
        x, y, t = q.popleft()
        if (x, y) == end:
            return t
        for dx, dy in DIRS:
            nx, ny = x + dx, y + dy
            nt = t + 1
            if 0 <= nx < n and 0 <= ny < m and not is_wall(nx, ny) and not is_wall(x, y):
                c = grid[nx][ny]
                # move allowed; if portal, check timing then teleport
                cand = []
                if c.isdigit():
                    X = int(c)
                    if X == 0 or nt % X == 0:
                        positions = portals[c]
                        # teleport to all same-digit positions (other cells); if only one, stays
                        for (px, py) in positions:
                            if (px, py) != (nx, ny):
                                cand.append((px, py))
                        if not positions or len(cand) == 0:
                            cand.append((nx, ny))
                    else:
                        continue
                else:
                    cand.append((nx, ny))
                tm = nt % L
                for (tx, ty) in cand:
                    if not vis[tx][ty][tm]:
                        vis[tx][ty][tm] = True
                        q.append((tx, ty, nt))
    return -1

if __name__ == "__main__":
    grid = [
        "S1.W",
        "..1E",
        "W..W"
    ]
    print(min_time(grid))
