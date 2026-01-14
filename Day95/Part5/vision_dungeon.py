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
        
        starts = []
        for _ in range(K):
            starts.append((int(next(iterator)), int(next(iterator))))
            
        grid = []
        for _ in range(N):
            grid.append(next(iterator))
    except StopIteration:
        return

    total_safe = 0
    for r in range(N):
        for c in range(M):
            if grid[r][c] != '#' and grid[r][c] != 'X':
                total_safe += 1
                
    queue = deque()
    visited = set()
    covered = 0
    
    for r, c in starts:
        if 0 <= r < N and 0 <= c < M and grid[r][c] != '#' and grid[r][c] != 'X':
            if (r, c) not in visited:
                visited.add((r, c))
                covered += 1
                queue.append((r, c))
                
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while queue:
        r, c = queue.popleft()
        
        for dr, dc in moves:
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#' and grid[nr][nc] != 'X':
                if (nr, nc) not in visited:
                    visited.add((nr, nc))
                    covered += 1
                    queue.append((nr, nc))
                    
    if covered == total_safe:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
