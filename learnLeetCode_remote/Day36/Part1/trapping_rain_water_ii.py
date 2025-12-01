from typing import List
import heapq

def trap_rain_water(heightMap: List[List[int]]) -> int:
    if not heightMap or not heightMap[0]:
        return 0
    m, n = len(heightMap), len(heightMap[0])
    vis = [[False]*n for _ in range(m)]
    pq = []  # (height, r, c)
    # push borders
    for r in range(m):
        for c in [0, n-1]:
            heapq.heappush(pq, (heightMap[r][c], r, c))
            vis[r][c] = True
    for c in range(n):
        for r in [0, m-1]:
            if not vis[r][c]:
                heapq.heappush(pq, (heightMap[r][c], r, c))
                vis[r][c] = True
    res = 0
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while pq:
        h, r, c = heapq.heappop(pq)
        for dr, dc in dirs:
            nr, nc = r+dr, c+dc
            if 0 <= nr < m and 0 <= nc < n and not vis[nr][nc]:
                vis[nr][nc] = True
                nh = heightMap[nr][nc]
                if h > nh:
                    res += h - nh
                heapq.heappush(pq, (max(h, nh), nr, nc))
    return res

if __name__ == "__main__":
    grid = [
        [1,4,3,1,3,2],
        [3,2,1,3,2,4],
        [2,3,3,2,3,1]
    ]
    print(trap_rain_water(grid))  # Expected 4
