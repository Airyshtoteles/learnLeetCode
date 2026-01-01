import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        R, C = int(line1[0]), int(line1[1])
        
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

    # BFS State: tuple of sorted positions
    queue = collections.deque()
    initial_state = (start,)
    queue.append((initial_state, 0))
    visited = {initial_state}
    
    # Moves: U, D, L, R
    # U: (-1, 0), (-1, 1)
    # D: (1, 0), (1, -1)
    # L: (0, -1), (-1, -1)
    # R: (0, 1), (1, 1)
    moves = [
        ((-1, 0), (-1, 1)), # U
        ((1, 0), (1, -1)),  # D
        ((0, -1), (-1, -1)),# L
        ((0, 1), (1, 1))    # R
    ]
    
    while queue:
        current_positions, steps = queue.popleft()
        
        if target in current_positions:
            print(steps)
            return
            
        for move in moves:
            next_positions = set()
            possible = True
            
            for r, c in current_positions:
                # Apply branches
                for dr, dc in move:
                    nr, nc = r + dr, c + dc
                    if not (0 <= nr < R and 0 <= nc < C) or grid[nr][nc] == '#':
                        possible = False
                        break
                    next_positions.add((nr, nc))
                if not possible: break
            
            if possible:
                next_state = tuple(sorted(list(next_positions)))
                if next_state not in visited:
                    visited.add(next_state)
                    queue.append((next_state, steps + 1))
                    
    print(-1)

if __name__ == "__main__":
    solve()
