import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        StartR, StartC, TargetR, TargetC = map(int, line2)
        
        grid = []
        for _ in range(N):
            grid.append(sys.stdin.readline().strip())
    except ValueError:
        return

    queue = collections.deque([(StartR, StartC)])
    visited = {(StartR, StartC)}
    
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    while queue:
        r, c = queue.popleft()
        
        if r == TargetR and c == TargetC:
            print("Possible")
            return
            
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#' and (nr, nc) not in visited:
                visited.add((nr, nc))
                queue.append((nr, nc))
                
    print("Impossible")

if __name__ == "__main__":
    solve()
