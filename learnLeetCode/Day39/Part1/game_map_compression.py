from collections import deque
from typing import List

def min_steps(grid: List[str]) -> int:
    n = len(grid)
    m = len(grid[0]) if n else 0
    if n == 0 or m == 0:
        return -1
    # Map keys to bit indices
    key_id = {}
    kid = 0
    for r in range(n):
        for c in range(m):
            if grid[r][c] == 'K':
                key_id[(r,c)] = kid
                kid += 1
    all_mask = (1 << kid) - 1

    def passable(r: int, c: int, mask: int) -> bool:
        ch = grid[r][c]
        if ch == '#':
            return False
        if ch == 'D' and mask != all_mask:
            return False
        return True

    start_mask = 0
    if grid[0][0] == '#':
        return -1
    if grid[0][0] == 'K':
        kid0 = key_id[(0,0)]
        start_mask |= 1 << kid0

    q = deque()
    q.append((0,0,start_mask,0))
    visited = [[[False]*(1<<kid) for _ in range(m)] for _ in range(n)]
    visited[0][0][start_mask] = True

    dirs = [(1,0),(-1,0),(0,1),(0,-1)]
    while q:
        r,c,mask,dist = q.popleft()
        if r == n-1 and c == m-1:
            return dist
        for dr,dc in dirs:
            nr, nc = r+dr, c+dc
            if 0 <= nr < n and 0 <= nc < m:
                nmask = mask
                ch = grid[nr][nc]
                if ch == 'K':
                    kid_idx = key_id[(nr,nc)]
                    nmask = mask | (1<<kid_idx)
                if passable(nr,nc,mask):
                    if not visited[nr][nc][nmask]:
                        visited[nr][nc][nmask] = True
                        q.append((nr,nc,nmask,dist+1))
    return -1

if __name__ == "__main__":
    grid = [
        ".K..",
        "##D.",
        "..#.",
        "...K",
    ]
    print(min_steps(grid))
