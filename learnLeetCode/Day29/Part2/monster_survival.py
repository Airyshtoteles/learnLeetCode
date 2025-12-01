from collections import deque
from typing import List, Tuple

def max_survival_time(m: int, n: int, monsters: List[Tuple[int,int]], start: Tuple[int,int]) -> int:
    INF = 10**9
    Tm = [[INF]*n for _ in range(m)]
    q = deque()
    for x,y in monsters:
        if 0 <= x < m and 0 <= y < n:
            Tm[x][y] = 0
            q.append((x,y))
    # multi-source BFS for monsters
    dirs = [(-1,0),(1,0),(0,-1),(0,1)]
    while q:
        x,y = q.popleft()
        for dx,dy in dirs:
            nx,ny = x+dx, y+dy
            if 0<=nx<m and 0<=ny<n and Tm[nx][ny] > Tm[x][y] + 1:
                Tm[nx][ny] = Tm[x][y] + 1
                q.append((nx,ny))
    sx, sy = start
    if not (0 <= sx < m and 0 <= sy < n):
        return -1
    if Tm[sx][sy] == 0:
        return -1
    # BFS for player
    Tp = [[-1]*n for _ in range(m)]
    Tp[sx][sy] = 0
    q.append((sx,sy))
    best = -1
    while q:
        x,y = q.popleft()
        t = Tp[x][y]
        if t < Tm[x][y]:
            if t > best:
                best = t
        for dx,dy in dirs:
            nx,ny = x+dx, y+dy
            if 0<=nx<m and 0<=ny<n and Tp[nx][ny] == -1:
                nt = t + 1
                # can move there, but only counts as safe if nt < Tm[nx][ny]
                Tp[nx][ny] = nt
                q.append((nx,ny))
    return best

if __name__ == "__main__":
    m,n = 5,5
    monsters = [(0,0),(4,4)]
    start=(2,2)
    print(max_survival_time(m,n,monsters,start))
