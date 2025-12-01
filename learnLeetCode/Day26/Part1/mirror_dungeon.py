from heapq import heappush, heappop
from typing import List

# Directions: 0=up,1=right,2=down,3=left
DIRS = [(-1,0),(0,1),(1,0),(0,-1)]
REFLECT_SLASH = [1,0,3,2]   # '/' : up->right, right->up, down->left, left->down
REFLECT_BACK  = [3,2,1,0]   # '\\': up->left, right->down, down->right, left->up


def min_mirror_flips(grid: List[str]) -> int:
    n = len(grid)
    if n == 0:
        return -1
    if grid[0][0] == '#':
        return -1
    INF = 10**9
    dist = [[[INF]*4 for _ in range(n)] for __ in range(n)]
    # start at (0,0) facing right (dir=1)
    dist[0][0][1] = 0
    pq = [(0, 0, 0, 1)]  # (cost,x,y,dir)

    def inb(x,y):
        return 0 <= x < n and 0 <= y < n

    while pq:
        cost, x, y, d = heappop(pq)
        if cost != dist[x][y][d]:
            continue
        if x == n-1 and y == n-1:
            return cost
        nx, ny = x + DIRS[d][0], y + DIRS[d][1]
        if not inb(nx, ny) or grid[nx][ny] == '#':
            continue
        c = grid[nx][ny]
        if c == '.':
            nd = d
            if cost < dist[nx][ny][nd]:
                dist[nx][ny][nd] = cost
                heappush(pq, (cost, nx, ny, nd))
        elif c == '/':
            nd_keep = REFLECT_SLASH[d]
            if cost < dist[nx][ny][nd_keep]:
                dist[nx][ny][nd_keep] = cost
                heappush(pq, (cost, nx, ny, nd_keep))
            nd_flip = REFLECT_BACK[d]
            if cost + 1 < dist[nx][ny][nd_flip]:
                dist[nx][ny][nd_flip] = cost + 1
                heappush(pq, (cost + 1, nx, ny, nd_flip))
        elif c == '\\':
            nd_keep = REFLECT_BACK[d]
            if cost < dist[nx][ny][nd_keep]:
                dist[nx][ny][nd_keep] = cost
                heappush(pq, (cost, nx, ny, nd_keep))
            nd_flip = REFLECT_SLASH[d]
            if cost + 1 < dist[nx][ny][nd_flip]:
                dist[nx][ny][nd_flip] = cost + 1
                heappush(pq, (cost + 1, nx, ny, nd_flip))
        else:
            # any other char treated as wall
            pass
    return -1


if __name__ == "__main__":
    n = 4
    grid = [
        ".#..",
        "..\\.",
        "#...",
        "...#",
    ]
    print(min_mirror_flips(grid))  # Expected 2
