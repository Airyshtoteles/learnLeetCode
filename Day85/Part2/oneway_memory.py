import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        R, C = int(line1[0]), int(line1[1])
        
        grid = []
        for _ in range(R):
            grid.append(sys.stdin.readline().strip())
    except ValueError:
        return

    start = (0, 0)
    target = (R-1, C-1)
    
    if grid[0][0] == '#' or grid[R-1][C-1] == '#':
        print("Impossible")
        return

    queue = collections.deque([start])
    visited = {start}
    
    while queue:
        r, c = queue.popleft()
        
        if (r, c) == target:
            print("Possible")
            return
            
        for dr, dc in [(0,1), (0,-1), (1,0), (-1,0)]:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < R and 0 <= nc < C:
                if grid[nr][nc] != '#' and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc))
                    
    print("Impossible")

if __name__ == "__main__":
    solve()
