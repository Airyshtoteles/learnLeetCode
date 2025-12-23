import heapq

def solve_bfs(start_r, start_c, R, C, grid):
    pq = []
    visited = set()
    
    current_power = grid[start_r][start_c]
    visited.add((start_r, start_c))
    count = 1
    
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    # Add neighbors
    for i in range(4):
        nr, nc = start_r + dr[i], start_c + dc[i]
        if 0 <= nr < R and 0 <= nc < C:
            heapq.heappush(pq, (grid[nr][nc], nr, nc))
            visited.add((nr, nc))
            
    while pq:
        val, r, c = pq[0] # Peek
        
        if current_power >= val:
            heapq.heappop(pq)
            current_power += val
            count += 1
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < R and 0 <= nc < C and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    heapq.heappush(pq, (grid[nr][nc], nr, nc))
        else:
            break
            
    return count

def solve():
    try:
        line = input().split()
        if not line:
            return
        R, C = int(line[0]), int(line[1])
        
        grid = []
        for _ in range(R):
            grid.append([int(x) for x in input().split()])
            
        max_val = -1
        for r in range(R):
            for c in range(C):
                if grid[r][c] > max_val:
                    max_val = grid[r][c]
                    
        max_revealed = 0
        for r in range(R):
            for c in range(C):
                if grid[r][c] == max_val:
                    max_revealed = max(max_revealed, solve_bfs(r, c, R, C, grid))
                    
        print(max_revealed)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
