import heapq
from typing import List

# LC 407 — Trapping Rain Water II
# Min-heap multi-source BFS from the border inward.

def trapRainWater(heightMap: List[List[int]]) -> int:
    if not heightMap or not heightMap[0]:
        return 0
    n, m = len(heightMap), len(heightMap[0])
    visited = [[False]*m for _ in range(n)]
    heap = []  # (height, x, y)

    # Push all border cells
    for i in range(n):
        for j in (0, m-1):
            heapq.heappush(heap, (heightMap[i][j], i, j))
            visited[i][j] = True
    for j in range(m):
        for i in (0, n-1):
            if not visited[i][j]:
                heapq.heappush(heap, (heightMap[i][j], i, j))
                visited[i][j] = True

    water = 0
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while heap:
        h, x, y = heapq.heappop(heap)
        for dx, dy in dirs:
            nx, ny = x+dx, y+dy
            if nx<0 or ny<0 or nx>=n or ny>=m or visited[nx][ny]:
                continue
            visited[nx][ny] = True
            nh = heightMap[nx][ny]
            if nh < h:
                water += h - nh
            heapq.heappush(heap, (max(h, nh), nx, ny))
    return water

if __name__ == "__main__":
    grid = [
        [1,4,3,1,3,2],
        [3,2,1,3,2,4],
        [2,3,3,2,3,1]
    ]
    print(trapRainWater(grid))  # 4
