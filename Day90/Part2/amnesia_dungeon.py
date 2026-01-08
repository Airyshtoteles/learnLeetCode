import sys
from collections import deque

def solve():
    try:
        line = sys.stdin.readline().split()
        if not line: return
        R, C = map(int, line)
        grid = [sys.stdin.readline().strip() for _ in range(R)]
    except ValueError:
        return

    if R == 0 or C == 0:
        print("NO")
        return

    if grid[0][0] == '#':
        print("NO")
        return

    queue = deque([(0, 0)])
    visited = set([(0, 0)])
    
    possible = False
    
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    while queue:
        r, c = queue.popleft()
        
        if r == R - 1 and c == C - 1:
            possible = True
            break
            
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            
            if 0 <= nr < R and 0 <= nc < C:
                if grid[nr][nc] != '#' and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc))
                    
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
