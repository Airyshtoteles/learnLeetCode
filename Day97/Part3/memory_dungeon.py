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
        K = int(next(iterator))
        
        grid = []
        start = None
        end = None
        for r in range(N):
            row = next(iterator)
            grid.append(row)
            for c in range(M):
                if row[c] == 'S':
                    start = (r, c)
                elif row[c] == 'E':
                    end = (r, c)
                    
    except StopIteration:
        return

    def manhattan(r, c):
        return abs(r - end[0]) + abs(c - end[1])
        
    curr_r, curr_c = start
    total_steps = 0
    max_iters = N * M * 2 
    iters = 0
    
    while (curr_r, curr_c) != end:
        # Local BFS limited by K
        q = deque([(curr_r, curr_c, 0)])
        visited = set([(curr_r, curr_c)])
        
        best_r, best_c = curr_r, curr_c
        best_h = manhattan(curr_r, curr_c)
        cost_to_best = 0
        
        while q:
            r, c, d = q.popleft()
            
            if d < K:
                for dr, dc in [(0,1), (0,-1), (1,0), (-1,0)]:
                    nr, nc = r + dr, c + dc
                    if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#' and (nr, nc) not in visited:
                        visited.add((nr, nc))
                        q.append((nr, nc, d+1))
                        
                        h = manhattan(nr, nc)
                        if h < best_h:
                            best_h = h
                            best_r, best_c = nr, nc
                            cost_to_best = d + 1
                            
        if best_h >= manhattan(curr_r, curr_c):
            print("-1")
            return
            
        curr_r, curr_c = best_r, best_c
        total_steps += cost_to_best
        
        iters += 1
        if iters > max_iters:
            print("-1")
            return
            
    print(total_steps)

if __name__ == "__main__":
    solve()
