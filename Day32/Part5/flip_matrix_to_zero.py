from collections import deque
from typing import List

def min_flips(mat: List[List[int]]) -> int:
    m, n = len(mat), len(mat[0])
    def idx(r,c): return r*n + c
    start = 0
    for r in range(m):
        for c in range(n):
            if mat[r][c] == 1:
                start |= 1 << idx(r,c)
    if start == 0:
        return 0
    masks = []
    dirs = [(1,0),(-1,0),(0,1),(0,-1),(0,0)]
    for r in range(m):
        for c in range(n):
            mask = 0
            for dr,dc in dirs:
                nr, nc = r+dr, c+dc
                if 0 <= nr < m and 0 <= nc < n:
                    mask |= 1 << idx(nr,nc)
            masks.append(mask)
    q = deque([(start,0)])
    visited = {start}
    while q:
        state, d = q.popleft()
        if state == 0:
            return d
        for mask in masks:
            ns = state ^ mask
            if ns not in visited:
                visited.add(ns)
                q.append((ns, d+1))
    return -1

if __name__ == "__main__":
    print(min_flips([[0,0],[0,1]]))  # Expected 3
