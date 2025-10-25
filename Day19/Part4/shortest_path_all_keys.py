# LC 864 — Shortest Path to Get All Keys
# BFS with bitmask of keys
from collections import deque
from typing import List

def shortestPathAllKeys(grid: List[str]) -> int:
    R, C = len(grid), len(grid[0])
    start = None
    total_keys = 0
    for i in range(R):
        for j in range(C):
            ch = grid[i][j]
            if ch == '@':
                start = (i, j)
            if 'a' <= ch <= 'f':
                total_keys = max(total_keys, ord(ch) - ord('a') + 1)
    all_mask = (1 << total_keys) - 1
    q = deque()
    visited = [[[False]*(1<<total_keys) for _ in range(C)] for __ in range(R)]
    sx, sy = start
    visited[sx][sy][0] = True
    q.append((sx, sy, 0, 0))  # x, y, mask, dist
    DIRS = [(1,0),(-1,0),(0,1),(0,-1)]
    while q:
        x, y, mask, dist = q.popleft()
        if mask == all_mask:
            return dist
        for dx, dy in DIRS:
            nx, ny = x+dx, y+dy
            if nx < 0 or ny < 0 or nx >= R or ny >= C:
                continue
            ch = grid[nx][ny]
            if ch == '#':
                continue
            nmask = mask
            if 'a' <= ch <= 'f':
                nmask |= 1 << (ord(ch) - ord('a'))
            if 'A' <= ch <= 'F':
                need = 1 << (ord(ch) - ord('A'))
                if (nmask & need) == 0:
                    continue
            if not visited[nx][ny][nmask]:
                visited[nx][ny][nmask] = True
                q.append((nx, ny, nmask, dist+1))
    return -1

if __name__ == "__main__":
    grid = ["@.a..","###.#","b.A.B"]
    print(shortestPathAllKeys(grid))  # 8
