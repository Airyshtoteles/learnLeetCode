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
        K = int(next(iterator))
        R = int(next(iterator))
        C = int(next(iterator))
    except StopIteration:
        return

    mazes = []
    for k in range(K):
        grid = []
        for r in range(R):
            grid.append(next(iterator))
        mazes.append(grid)

    # BFS
    # State is tuple of (r, c) for each maze
    start_pos = tuple((0, 0) for _ in range(K))
    target_pos = (R - 1, C - 1)
    
    queue = deque([(start_pos, 0)])
    visited = {start_pos}
    
    moves = [(-1, 0), (1, 0), (0, -1), (0, 1)]
    
    while queue:
        current_state, dist = queue.popleft()
        
        # Check if all at target
        all_reached = True
        for pos in current_state:
            if pos != target_pos:
                all_reached = False
                break
        
        if all_reached:
            print(dist)
            return

        for move in moves:
            dr, dc = move
            next_positions = []
            
            for k in range(K):
                r, c = current_state[k]
                nr, nc = r + dr, c + dc
                
                # Logic: Move if valid, else stay
                if 0 <= nr < R and 0 <= nc < C and mazes[k][nr][nc] != '#':
                    next_positions.append((nr, nc))
                else:
                    next_positions.append((r, c))
            
            next_state = tuple(next_positions)
            
            if next_state not in visited:
                visited.add(next_state)
                queue.append((next_state, dist + 1))
                
    print("-1")

if __name__ == "__main__":
    solve()
