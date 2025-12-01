from collections import deque
from typing import List

def winner_after_expansion(grid: List[List[str]]) -> str:
    if not grid or not grid[0]:
        return "Draw"
    n, m = len(grid), len(grid[0])
    A, B = 1, 2
    owner = [[-1]*m for _ in range(n)]  # -1=unreached,0=contested,1=A,2=B
    dist = [[-1]*m for _ in range(n)]
    q = deque()
    cntA = cntB = 0
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'A':
                owner[i][j] = A
                dist[i][j] = 0
                q.append((i,j,0,A))
                cntA += 1
            elif grid[i][j] == 'B':
                owner[i][j] = B
                dist[i][j] = 0
                q.append((i,j,0,B))
                cntB += 1
    dirs = [(-1,0),(1,0),(0,-1),(0,1)]
    while q:
        x,y,t,typ = q.popleft()
        # no expansion from contested
        if owner[x][y] == 0:
            continue
        for dx,dy in dirs:
            nx,ny = x+dx, y+dy
            if nx<0 or nx>=n or ny<0 or ny>=m:
                continue
            if grid[nx][ny] != '.':
                continue
            if dist[nx][ny] == -1:
                dist[nx][ny] = t+1
                owner[nx][ny] = typ
                q.append((nx,ny,t+1,typ))
                if typ == A:
                    cntA += 1
                else:
                    cntB += 1
            else:
                if dist[nx][ny] == t+1 and owner[nx][ny] != 0 and owner[nx][ny] != typ:
                    # tie -> contested; remove previously added count
                    if owner[nx][ny] == A:
                        cntA -= 1
                    elif owner[nx][ny] == B:
                        cntB -= 1
                    owner[nx][ny] = 0
                # else if reached earlier or by same type, ignore
    if cntA > cntB:
        return "A"
    if cntB > cntA:
        return "B"
    return "Draw"

if __name__ == "__main__":
    grid = [
        ["A",".","."],
        [".","B","."],
        [".",".","."]
    ]
    print(winner_after_expansion(grid))  # Example result
