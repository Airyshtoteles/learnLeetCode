from collections import deque

def solve():
    # Hardcoded Input for demonstration
    # 5x5 Maze
    # Player Maze:
    # S . . # .
    # . # . . .
    # . . . # .
    # # . # . .
    # . . . . G
    
    # Shadow Maze (Parallel):
    # . . # . .
    # . # . . .
    # . . . # .
    # . # . . .
    # S . . . .
    
    # Linked Pairs (Forbidden states):
    # If Player at (2,2) and Shadow at (2,2) -> Die
    
    M, N = 5, 5
    player_grid = [
        "S..#.",
        ".#...",
        "...#.",
        "#.#!.", # ! is just empty, fixing length
        "....G"
    ]
    # Fix the 4th line length manually or just parse carefully
    player_grid = [
        "S..#.",
        ".#...",
        "...#.",
        "#.#..",
        "....G"
    ]
    
    shadow_grid = [
        ".....",
        ".....",
        ".....",
        ".....",
        "....S"
    ]
    
    # Find start/goal
    start_p = None
    goal_p = None
    start_s = None
    
    for r in range(M):
        for c in range(N):
            if player_grid[r][c] == 'S':
                start_p = (r, c)
            if player_grid[r][c] == 'G':
                goal_p = (r, c)
            if shadow_grid[r][c] == 'S':
                start_s = (r, c)
                
    # Linked pairs (Forbidden)
    # Let's say (2,2) for both is forbidden
    forbidden = set()
    # forbidden.add( ((2,2), (2,2)) )
    
    # BFS
    # State: (pr, pc, sr, sc)
    queue = deque()
    initial_state = (start_p[0], start_p[1], start_s[0], start_s[1])
    queue.append((initial_state, 0))
    
    visited = set()
    visited.add(initial_state)
    
    # Directions: U, D, L, R
    # Player: (-1,0), (1,0), (0,-1), (0,1)
    # Shadow: (1,0), (-1,0), (0,1), (0,-1) (Inverse)
    moves = [
        ((-1, 0), (1, 0)),  # Up / Down
        ((1, 0), (-1, 0)),  # Down / Up
        ((0, -1), (0, 1)),  # Left / Right
        ((0, 1), (0, -1))   # Right / Left
    ]
    
    while queue:
        (pr, pc, sr, sc), steps = queue.popleft()
        
        if (pr, pc) == goal_p:
            return steps
        
        for (dpr, dpc), (dsr, dsc) in moves:
            npr, npc = pr + dpr, pc + dpc
            nsr, nsc = sr + dsr, sc + dsc
            
            # Check bounds
            if not (0 <= npr < M and 0 <= npc < N): continue
            if not (0 <= nsr < M and 0 <= nsc < N): continue
            
            # Check walls
            if player_grid[npr][npc] == '#': continue
            if shadow_grid[nsr][nsc] == '#': continue
            
            # Check forbidden
            if ((npr, npc), (nsr, nsc)) in forbidden: continue
            
            new_state = (npr, npc, nsr, nsc)
            if new_state not in visited:
                visited.add(new_state)
                queue.append((new_state, steps + 1))
                
    return -1

if __name__ == "__main__":
    result = solve()
    print(f"Minimum steps to goal: {result}")
