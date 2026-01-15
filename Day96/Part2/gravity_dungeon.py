import sys
import heapq

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

    # Gravity: Down(0), Left(1), Up(2), Right(3)
    # Directions for GRAVITY
    g_dr = [1, 0, -1, 0]
    g_dc = [0, -1, 0, 1]
    
    # Moves: R, L, D, U
    m_dr = [0, 0, 1, -1]
    m_dc = [1, -1, 0, 0]
    
    # Dijkstra
    # State: (time, r, c)
    # Visited: (r, c, time % 4K)
    
    cycle = 4 * K
    dist = {} # (r, c, mod) -> min_time
    
    pq = [(0, start[0], start[1])]
    dist[(start[0], start[1], 0)] = 0
    
    while pq:
        t, r, c = heapq.heappop(pq)
        
        mod = t % cycle
        if dist.get((r, c, mod), float('inf')) < t:
            continue
            
        if (r, c) == end:
            print(t)
            return

        # Try 4 moves
        for i in range(4):
            nr, nc = r + m_dr[i], c + m_dc[i]
            
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#':
                nt = t + 1
                
                # Apply Gravity
                g_idx = (nt // K) % 4
                
                curr_r, curr_c = nr, nc
                
                # Simulate fall
                while True:
                    next_r, next_c = curr_r + g_dr[g_idx], curr_c + g_dc[g_idx]
                    
                    if 0 <= next_r < N and 0 <= next_c < M and grid[next_r][next_c] != '#':
                        curr_r, curr_c = next_r, next_c
                        if (curr_r, curr_c) == end:
                            break
                    else:
                        break # Hit wall
                
                n_mod = nt % cycle
                old_min = dist.get((curr_r, curr_c, n_mod), float('inf'))
                if nt < old_min:
                    dist[(curr_r, curr_c, n_mod)] = nt
                    heapq.heappush(pq, (nt, curr_r, curr_c))
                    
    print("-1")

if __name__ == "__main__":
    solve()
