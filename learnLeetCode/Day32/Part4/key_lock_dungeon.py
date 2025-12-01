from collections import deque
from typing import List

def shortest_path_all_keys(grid: List[str]) -> int:
    m, n = len(grid), len(grid[0])
    sr = sc = -1
    allmask = 0
    for r in range(m):
        for c in range(n):
            ch = grid[r][c]
            if ch == '@':
                sr, sc = r, c
            if 'a' <= ch <= 'f':
                allmask |= 1 << (ord(ch) - ord('a'))
    q = deque([(sr, sc, 0, 0)])  # r,c,mask,dist
    visited = set([(sr, sc, 0)])
    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while q:
        r,c,mask,d = q.popleft()
        if mask == allmask:
            return d
        for dr,dc in dirs:
            nr, nc = r+dr, c+dc
            if not (0 <= nr < m and 0 <= nc < n):
                continue
            ch = grid[nr][nc]
            if ch == '#':
                continue
            nmask = mask
            if 'a' <= ch <= 'f':
                nmask |= 1 << (ord(ch) - ord('a'))
            if 'A' <= ch <= 'F':
                need = 1 << (ord(ch) - ord('A'))
                if (nmask & need) == 0:
                    continue
            state = (nr,nc,nmask)
            if state in visited:
                continue
            visited.add(state)
            q.append((nr,nc,nmask,d+1))
    return -1

if __name__ == "__main__":
    grid = ["@.a.#","###.#","b.A.B"]
    print(shortest_path_all_keys(grid))  # Expected 8
