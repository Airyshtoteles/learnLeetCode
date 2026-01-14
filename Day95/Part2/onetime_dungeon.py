import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        grid = []
        for _ in range(N):
            grid.append(next(iterator))
    except StopIteration:
        return

    # BFS
    queue = deque()
    visited = set()
    
    # Enqueue Row 0
    for c in range(M):
        if grid[0][c] != '#':
            state = (0, c)
            queue.append(state)
            visited.add(state)
            
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    reached = False
    
    while queue:
        r, c = queue.popleft()
        
        if r == N - 1:
            reached = True
            break
            
        for dr, dc in moves:
            nr, nc = r + dr, c + dc
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#':
                if (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc))
                    
    if reached:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
