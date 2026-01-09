import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        R, C, K = int(line1[0]), int(line1[1]), int(line1[2])
        
        grid = []
        start = None
        target = None
        for r in range(R):
            row = sys.stdin.readline().strip()
            grid.append(row)
            for c, char in enumerate(row):
                if char == 'S': start = (r, c)
                if char == 'T': target = (r, c)
    except ValueError:
        return

    if not start or not target:
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
