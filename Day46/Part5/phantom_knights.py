import collections
import math

def solve():
    # Hardcoded Input
    # 8x8 Grid
    N = 8
    M = 8
    D = 8.0 # Max distance
    
    # 0: Empty, 1: Wall, 2: Rune
    grid = [
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 2, 0, 0, 0],
        [0, 0, 1, 1, 1, 1, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0],
        [0, 0, 1, 1, 1, 1, 0, 0],
        [0, 2, 0, 0, 0, 0, 0, 0],
        [0, 0, 0, 0, 0, 0, 0, 0]
    ]
    
    start1 = (0, 0)
    start2 = (0, 2)
    target = (7, 7)
    
    # Knight moves
    moves = [
        (-2, -1), (-2, 1), (-1, -2), (-1, 2),
        (1, -2), (1, 2), (2, -1), (2, 1)
    ]
    
    # State: (r1, c1, r2, c2, pending_who, timer)
    # pending_who: 0=None, 1=Wait for K1, 2=Wait for K2
    initial_state = (start1[0], start1[1], start2[0], start2[1], 0, 0)
    
    queue = collections.deque([(0, initial_state)])
    visited = set([initial_state])
    
    while queue:
        steps, state = queue.popleft()
        r1, c1, r2, c2, pending, timer = state
        
        if (r1, c1) == target and (r2, c2) == target:
            print(f"Minimum Steps: {steps}")
            return
        
        # Generate moves for K1
        next_k1 = []
        for dr, dc in moves:
            nr, nc = r1 + dr, c1 + dc
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != 1:
                next_k1.append((nr, nc))
                
        # Generate moves for K2
        next_k2 = []
        for dr, dc in moves:
            nr, nc = r2 + dr, c2 + dc
            if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != 1:
                next_k2.append((nr, nc))
                
        # Combine
        for nr1, nc1 in next_k1:
            for nr2, nc2 in next_k2:
                # Check Distance
                dist = math.sqrt((nr1 - nr2)**2 + (nc1 - nc2)**2)
                if dist > D:
                    continue
                
                # Check Rune Logic
                on_rune_1 = (grid[nr1][nc1] == 2)
                on_rune_2 = (grid[nr2][nc2] == 2)
                
                n_pending = pending
                n_timer = timer
                
                valid_move = True
                
                if pending == 0:
                    if on_rune_1 and not on_rune_2:
                        n_pending = 2 # Wait for K2
                        n_timer = 3
                    elif not on_rune_1 and on_rune_2:
                        n_pending = 1 # Wait for K1
                        n_timer = 3
                    else:
                        # Both on rune or neither
                        n_pending = 0
                        n_timer = 0
                elif pending == 1: # Waiting for K1
                    if on_rune_1:
                        n_pending = 0
                        n_timer = 0
                    else:
                        n_timer -= 1
                        if n_timer == 0:
                            valid_move = False
                elif pending == 2: # Waiting for K2
                    if on_rune_2:
                        n_pending = 0
                        n_timer = 0
                    else:
                        n_timer -= 1
                        if n_timer == 0:
                            valid_move = False
                            
                if valid_move:
                    new_state = (nr1, nc1, nr2, nc2, n_pending, n_timer)
                    if new_state not in visited:
                        visited.add(new_state)
                        queue.append((steps + 1, new_state))
                        
    print("-1")

if __name__ == "__main__":
    solve()
