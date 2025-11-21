import collections
import sys

def solve():
    # Example Input Hardcoded for demonstration
    # N=5, M=5
    # World 0:
    # S...#
    # .###.
    # .....
    # .###.
    # ....E
    # World 1:
    # .....
    # #...#
    # #.#.#
    # #...#
    # .....
    # Rifts at (0, 4), (2, 2), (4, 0)
    
    N, M = 5, 5
    grid0 = [
        "S...#",
        ".###.",
        ".....",
        ".###.",
        "....E"
    ]
    grid1 = [
        ".....",
        "#...#",
        "#.R.#", # Let's say R is just a marker for visual, but input gives list
        "#...#",
        "....."
    ]
    
    # Rifts coordinates (0-indexed)
    rifts = {
        (0, 4),
        (2, 2),
        (4, 0)
    }
    
    # Find Start and End
    start_pos = None
    end_pos = None
    
    # Scan Grid 0 for S (Start is always in World 0)
    for r in range(N):
        for c in range(M):
            if grid0[r][c] == 'S':
                start_pos = (r, c)
            if grid0[r][c] == 'E':
                end_pos = (r, c)
    
    # If E not in Grid 0, check Grid 1 (though usually E is a coordinate)
    if end_pos is None:
        for r in range(N):
            for c in range(M):
                if grid1[r][c] == 'E':
                    end_pos = (r, c)
                    
    if start_pos is None or end_pos is None:
        print("Start or End not found")
        return

    # 0-1 BFS
    # dist[world][r][c]
    INF = float('inf')
    dist = [[[INF] * M for _ in range(N)] for _ in range(2)]
    
    sr, sc = start_pos
    dist[0][sr][sc] = 0
    
    dq = collections.deque()
    dq.append((0, sr, sc)) # world, r, c
    
    directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while dq:
        w, r, c = dq.popleft()
        
        d = dist[w][r][c]
        
        # Check if reached End
        if (r, c) == end_pos:
            print(f"Minimum steps: {d}")
            return

        # 1. Try Teleport (Cost 0)
        if (r, c) in rifts:
            nw = 1 - w
            # Check if target cell is not a wall
            target_grid = grid0 if nw == 0 else grid1
            if target_grid[r][c] != '#':
                if dist[nw][r][c] > d:
                    dist[nw][r][c] = d
                    dq.appendleft((nw, r, c)) # Push front for cost 0
        
        # 2. Try Move (Cost 1)
        curr_grid = grid0 if w == 0 else grid1
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < N and 0 <= nc < M:
                if curr_grid[nr][nc] != '#':
                    if dist[w][nr][nc] > d + 1:
                        dist[w][nr][nc] = d + 1
                        dq.append((w, nr, nc)) # Push back for cost 1

    print("Unreachable")

if __name__ == "__main__":
    solve()
