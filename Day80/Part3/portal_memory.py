import sys
from collections import deque

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        R = int(next(iterator))
        C = int(next(iterator))
        grid = []
        for _ in range(R):
            grid.append(next(iterator))
    except StopIteration:
        return

    startR, startC = -1, -1
    targetR, targetC = -1, -1

    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'S':
                startR, startC = r, c
            elif grid[r][c] == 'T':
                targetR, targetC = r, c

    q = deque([(startR, startC)])
    visited = set([(startR, startC)])
    
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    reachable = False
    
    while q:
        r, c = q.popleft()
        
        if r == targetR and c == targetC:
            reachable = True
            break
        
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            
            if 0 <= nr < R and 0 <= nc < C:
                cell = grid[nr][nc]
                if cell != '#' and cell != 'P' and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    q.append((nr, nc))
                    
    if reachable:
        print("true")
    else:
        print("false")

if __name__ == "__main__":
    solve()
