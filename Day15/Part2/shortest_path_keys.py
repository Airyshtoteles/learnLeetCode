from collections import deque
from typing import List, Tuple

# LeetCode 864 — Shortest Path to Get All Keys
# BFS with state (x, y, keysMask). Keys up to 6 → mask in [0..63].

DIRS = [(1,0),(-1,0),(0,1),(0,-1)]

def shortestPathAllKeys(grid: List[str]) -> int:
    n, m = len(grid), len(grid[0])
    sx = sy = -1
    all_keys_mask = 0
    for i in range(n):
        for j in range(m):
            c = grid[i][j]
            if c == '@':
                sx, sy = i, j
            if 'a' <= c <= 'f':
                all_keys_mask |= 1 << (ord(c) - ord('a'))

    q = deque()
    q.append((sx, sy, 0, 0))  # x,y,mask,dist
    visited = [[[False]*64 for _ in range(m)] for __ in range(n)]
    visited[sx][sy][0] = True

    while q:
        x, y, mask, d = q.popleft()
        if mask == all_keys_mask:
            return d
        for dx, dy in DIRS:
            nx, ny = x+dx, y+dy
            if nx<0 or ny<0 or nx>=n or ny>=m: continue
            c = grid[nx][ny]
            if c == '#': continue
            nmask = mask
            if 'a' <= c <= 'f':
                nmask |= 1 << (ord(c)-ord('a'))
            if 'A' <= c <= 'F':
                if not (mask & (1 << (ord(c)-ord('A')))):
                    continue
            if not visited[nx][ny][nmask]:
                visited[nx][ny][nmask] = True
                q.append((nx, ny, nmask, d+1))
    return -1

if __name__ == "__main__":
    print(shortestPathAllKeys(["@.a.#","###.#","b.A.B"]))  # Expected 8
