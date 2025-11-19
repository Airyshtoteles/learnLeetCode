from heapq import heappush, heappop
from typing import List, Tuple

def min_walls_rotating_maze(grid: List[str]) -> int:
    if not grid:
        return -1
    n, m = len(grid), len(grid[0])
    INF = 10**9
    dist = [[[INF]*10 for _ in range(m)] for __ in range(n)]
    dist[0][0][0] = 0
    pq: List[Tuple[int,int,int,int]] = [(0,0,0,0)]  # cost,r,c,tmod
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while pq:
        cost,r,c,tmod = heappop(pq)
        if cost != dist[r][c][tmod]:
            continue
        if r==n-1 and c==m-1:
            return cost
        ntmod = (tmod + 1) % 10
        phase = ((tmod + 1)//5) % 2  # phase after move
        for dr,dc in dirs:
            nr, nc = r+dr, c+dc
            if 0 <= nr < n and 0 <= nc < m:
                ch = grid[nr][nc]
                add = 0
                if ch == 'R':
                    add = 1
                elif ch == '#':
                    # free only in inverted phase (phase==1)
                    if phase == 0:
                        add = 1
                # '.' always free
                ncost = cost + add
                if ncost < dist[nr][nc][ntmod]:
                    dist[nr][nc][ntmod] = ncost
                    heappush(pq,(ncost,nr,nc,ntmod))
    return min(dist[n-1][m-1]) if min(dist[n-1][m-1])<INF else -1

if __name__ == "__main__":
    maze = [".#.","R#.","..#"]
    print(min_walls_rotating_maze(maze))
