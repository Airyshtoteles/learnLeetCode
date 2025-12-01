from collections import deque
from math import gcd
from typing import List, Tuple

def lcm(a: int, b: int) -> int:
    return a // gcd(a,b) * b if a and b else a or b

def is_open(initial: str, k: int, t: int) -> bool:
    if initial in ('S','E'):
        initial = '.'
    if k == 0:
        return initial != '#'
    flips = (t // k) % 2
    if flips == 0:
        return initial != '#'
    else:
        return initial == '#'

def min_time(grid: List[List[str]], flip: List[List[int]]) -> int:
    n = len(grid); m = len(grid[0]) if n else 0
    if n == 0 or m == 0:
        return -1
    S = E = None
    L = 1
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'S': S = (i,j)
            if grid[i][j] == 'E': E = (i,j)
            k = flip[i][j]
            if k > 0:
                L = lcm(L, 2*k)
    if S is None or E is None:
        return -1
    # BFS with waiting; state includes time mod L
    q = deque()
    q.append((S[0], S[1], 0))
    visited = [[[False]*L for _ in range(m)] for __ in range(n)] if L>0 else None
    visited[S[0]][S[1]][0] = True
    dirs = [(-1,0),(1,0),(0,-1),(0,1),(0,0)]  # last is wait
    while q:
        x,y,t = q.popleft()
        if (x,y) == E:
            return t
        for dx,dy in dirs:
            nx,ny = x+dx, y+dy
            nt = t+1
            if 0<=nx<n and 0<=ny<m:
                if is_open(grid[x][y], flip[x][y], t) and is_open(grid[nx][ny], flip[nx][ny], nt):
                    tm = nt % L if L>0 else 0
                    if not visited[nx][ny][tm]:
                        visited[nx][ny][tm] = True
                        q.append((nx,ny,nt))
    return -1

if __name__ == "__main__":
    grid = [
        ['S','.','#'],
        ['.','#','E']
    ]
    flip = [
        [0,2,1],
        [3,0,2]
    ]
    print(min_time(grid, flip))  # Expected 5
