from collections import deque

def solve_dungeon_switchboard(n, colors, edges, s, t):
    # Build adjacency list
    adj = [[] for _ in range(n)]
    for u, v, has_switch in edges:
        adj[u].append((v, has_switch))
        adj[v].append((u, has_switch))
        
    # BFS State: (u, phase)
    # phase: 0, 1, 2
    # Distance map
    dist = {}
    
    # Initial check: Can we be at S?
    # Problem says "You start at S". Usually implies S is valid initially.
    # But let's check: (Colors[S] + 0) % 3 == 1 (Green).
    # If not, maybe we can't even start? Or maybe start is always safe?
    # "Kamu hanya bisa kamu masuki bila warnanya sedang Green."
    # Usually start is entered at t=0.
    # Let's assume we are already IN S, so we don't check entry condition for S at t=0.
    # But if we return to S, we check.
    
    queue = deque([(s, 0, 0)]) # u, phase, steps
    dist[(s, 0)] = 0
    
    while queue:
        u, phase, steps = queue.popleft()
        
        if u == t:
            return steps
        
        for v, has_switch in adj[u]:
            next_phase = (phase + 1) % 3 if has_switch else phase
            
            # Check if we can enter v
            # Condition: (Colors[v] + next_phase) % 3 == 1 (Green)
            current_color_v = (colors[v] + next_phase) % 3
            
            if current_color_v == 1:
                if (v, next_phase) not in dist:
                    dist[(v, next_phase)] = steps + 1
                    queue.append((v, next_phase, steps + 1))
                    
    return -1

if __name__ == "__main__":
    N = 3
    # 0=Red, 1=Green, 2=Blue
    Colors = [1, 0, 0] 
    Edges = [
        [0, 1, 1], # Switch
        [1, 2, 0]  # Normal
    ]
    S = 0
    T = 2
    
    result = solve_dungeon_switchboard(N, Colors, Edges, S, T)
    print(f"Minimum Steps: {result}")
