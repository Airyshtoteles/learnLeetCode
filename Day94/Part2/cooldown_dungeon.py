import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        R = int(next(iterator))
        C_grid = int(next(iterator))
        Cooldown = int(next(iterator))
        grid = []
        for _ in range(R):
            grid.append(next(iterator))
    except StopIteration:
        return

    # Helper to encode state
    def encode(w):
        val = 0
        mult = 1
        for x in w:
            val += x * mult
            mult *= (Cooldown + 1)
        return val

    # BFS
    # State: (r, c, (w0, w1, w2, w3))
    # Using tuple for python visited set
    start_state = (0, 0, (0, 0, 0, 0))
    queue = deque([(start_state, 0)])
    visited = {start_state}
    
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    while queue:
        (r, c, w), dist = queue.popleft()
        
        if r == R - 1 and c == C_grid - 1:
            print(f"YES {dist}")
            return
            
        for i in range(4):
            if w[i] > 0:
                continue
                
            nr, nc = r + dr[i], c + dc[i]
            
            if 0 <= nr < R and 0 <= nc < C_grid and grid[nr][nc] != '#':
                next_w_list = []
                for k in range(4):
                    if k == i:
                        next_w_list.append(Cooldown)
                    else:
                        next_w_list.append(max(0, w[k] - 1))
                
                next_w = tuple(next_w_list)
                next_state = (nr, nc, next_w)
                
                if next_state not in visited:
                    visited.add(next_state)
                    queue.append((next_state, dist + 1))
                    
    print("NO")

if __name__ == "__main__":
    solve()
