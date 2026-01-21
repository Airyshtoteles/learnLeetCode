import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        K = int(next(iterator))
        N = int(next(iterator))
        M = int(next(iterator))
        
        agents = []
        for _ in range(K):
            r = int(next(iterator))
            c = int(next(iterator))
            agents.append((r,c))
            
        TargetR = int(next(iterator))
        TargetC = int(next(iterator))
        
        grid = []
        for _ in range(N):
            grid.append(next(iterator))
    except StopIteration:
        return

    # BFS from Target
    visited = [[False for _ in range(M)] for _ in range(N)]
    queue = deque()
    
    if 0 <= TargetR < N and 0 <= TargetC < M and grid[TargetR][TargetC] != '#':
        queue.append((TargetR, TargetC))
        visited[TargetR][TargetC] = True
        
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    while queue:
        r, c = queue.popleft()
        
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#':
                if not visited[nr][nc]:
                    visited[nr][nc] = True
                    queue.append((nr, nc))
                    
    possible = False
    for r, c in agents:
        if 0 <= r < N and 0 <= c < M and visited[r][c]:
            possible = True
            break
            
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
