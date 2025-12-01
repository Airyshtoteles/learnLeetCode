# LC 407 — Trapping Rain Water II
# Min-heap BFS from the border
import heapq
from typing import List

def trapRainWater(heightMap: List[List[int]]) -> int:
    n = len(heightMap)
    if n == 0:
        return 0
    m = len(heightMap[0])
    if m == 0:
        return 0
    visited = [[False]*m for _ in range(n)]
    pq = []  # (height, x, y)
    # push borders
    for i in range(n):
        heapq.heappush(pq, (heightMap[i][0], i, 0)); visited[i][0] = True
        if m > 1:
            heapq.heappush(pq, (heightMap[i][m-1], i, m-1)); visited[i][m-1] = True
    for j in range(m):
        if not visited[0][j]:
            heapq.heappush(pq, (heightMap[0][j], 0, j)); visited[0][j] = True
        if n > 1 and not visited[n-1][j]:
            heapq.heappush(pq, (heightMap[n-1][j], n-1, j)); visited[n-1][j] = True
    ans = 0
    DIRS = [(1,0),(-1,0),(0,1),(0,-1)]
    while pq:
        h, x, y = heapq.heappop(pq)
        for dx, dy in DIRS:
            nx, ny = x+dx, y+dy
            if nx < 0 or ny < 0 or nx >= n or ny >= m or visited[nx][ny]:
                continue
            visited[nx][ny] = True
            nh = heightMap[nx][ny]
            if nh < h:
                ans += (h - nh)
            heapq.heappush(pq, (max(h, nh), nx, ny))
    return ans

if __name__ == "__main__":
    grid = [
        [1,4,3,1,3,2],
        [3,2,1,3,2,4],
        [2,3,3,2,3,1]
    ]
    print(trapRainWater(grid))  # 4
