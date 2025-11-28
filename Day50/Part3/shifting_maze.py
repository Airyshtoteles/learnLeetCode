import heapq

def solve_shifting_maze(maze, k):
    M = len(maze)
    N = len(maze[0])
    
    # Precompute wall locations for fast query
    # walls[r] = list of column indices where walls are initially
    walls = []
    for r in range(M):
        row_walls = [c for c, char in enumerate(maze[r]) if char == '#']
        walls.append(row_walls)
        
    def is_wall(r, c, t):
        # Wall at (r, c) at time t if any original wall at (r, k) 
        # such that k + (something) reaches c?
        # Rule: Wall at k spreads to k+1 at t=1, k+2 at t=2...
        # So wall at k reaches c at time t if k + t >= c.
        # Condition: exists wall at col k <= c such that k + t >= c.
        # i.e., k >= c - t.
        # So we check if there is any wall in row r with index in [c-t, c].
        
        # Optimization: Check the rightmost wall in row r that is <= c.
        # If its index >= c - t, then it covers c.
        
        row_w = walls[r]
        # Binary search or just iterate?
        # Since we want rightmost <= c.
        # We can use bisect_right.
        import bisect
        idx = bisect.bisect_right(row_w, c)
        if idx > 0:
            rightmost_wall_idx = row_w[idx - 1]
            if rightmost_wall_idx >= c - t:
                return True
        return False

    # Dijkstra: (flips, time, r, c)
    pq = [(0, 0, 0, 0)]
    visited = {} # (r, c) -> (flips, time)
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0), (0, 0)] # Wait is allowed
    
    while pq:
        flips, time, r, c = heapq.heappop(pq)
        
        if r == M - 1 and c == N - 1:
            return True
        
        if flips > k:
            continue
            
        if (r, c) in visited:
            v_flips, v_time = visited[(r, c)]
            if v_flips < flips: continue
            if v_flips == flips and v_time <= time: continue
            
        visited[(r, c)] = (flips, time)
        
        next_time = time + 1
        
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < M and 0 <= nc < N:
                # Calculate cost
                # If next cell is wall at next_time, cost + 1
                cost = 1 if is_wall(nr, nc, next_time) else 0
                
                new_flips = flips + cost
                
                if new_flips <= k:
                    # Optimization: Don't add if we already found a better path to (nr, nc)
                    if (nr, nc) not in visited or \
                       (visited[(nr, nc)][0] > new_flips) or \
                       (visited[(nr, nc)][0] == new_flips and visited[(nr, nc)][1] > next_time):
                        heapq.heappush(pq, (new_flips, next_time, nr, nc))
                        
    return False

if __name__ == "__main__":
    maze = [
        "S..",
        "#..",
        "..E"
    ]
    # S at (0,0), E at (2,2).
    # Wall at (1,0).
    # t=0: (1,0) is #.
    # t=1: (1,0), (1,1) are #.
    # t=2: (1,0), (1,1), (1,2) are #.
    
    k = 0
    print(f"Possible: {solve_shifting_maze(maze, k)}")
