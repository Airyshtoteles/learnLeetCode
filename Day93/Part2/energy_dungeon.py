import sys
from collections import deque

def solve():
    try:
        input_data = sys.stdin.read().split()
    except Exception:
        return
        
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        R = int(next(iterator))
        C = int(next(iterator))
        StartR = int(next(iterator))
        StartC = int(next(iterator))
        EndR = int(next(iterator))
        EndC = int(next(iterator))
        InitialEnergy = int(next(iterator))
    except StopIteration:
        return
        
    grid = []
    for _ in range(R):
        grid.append(next(iterator))
        
    # Standard BFS
    visited = [[False for _ in range(C)] for _ in range(R)]
    queue = deque([(StartR, StartC, 0)])
    visited[StartR][StartC] = True
    
    moves = [(-1,0), (1,0), (0,-1), (0,1)]
    
    while queue:
        r, c, dist = queue.popleft()
        
        if r == EndR and c == EndC:
            print(f"YES {dist}")
            return
            
        current_energy = InitialEnergy - dist
        if current_energy <= 0:
            continue
            
        for dr, dc in moves:
            nr, nc = r + dr, c + dc
            if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#':
                if not visited[nr][nc]:
                    visited[nr][nc] = True
                    queue.append((nr, nc, dist + 1))
                    
    print("NO")

if __name__ == "__main__":
    solve()
