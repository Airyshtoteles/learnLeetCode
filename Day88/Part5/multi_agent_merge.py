import sys
import collections
import itertools

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, K = map(int, line1)
        
        starts = []
        for _ in range(K):
            starts.append(tuple(map(int, sys.stdin.readline().split()))) # (r, c)
            
        line_t = sys.stdin.readline().split()
        if not line_t: return
        Target = tuple(map(int, line_t))
        
        grid = []
        for _ in range(N):
            grid.append(sys.stdin.readline().strip())
    except ValueError:
        return

    # BFS
    # State: sorted tuple of (r,c)
    initial_state = sorted(starts)
    initial_tuple = tuple(initial_state)
    
    queue = collections.deque([initial_tuple])
    visited = {initial_tuple}
    
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    while queue:
        current_agents = queue.popleft()
        
        if any(pos == Target for pos in current_agents):
            print("Possible")
            return
            
        # Generate moves
        agent_options = []
        possible = True
        
        for r, c in current_agents:
            opts = []
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < N and 0 <= nc < M and grid[nr][nc] != '#':
                    opts.append((nr, nc))
            
            if not opts:
                possible = False
                break
            agent_options.append(opts)
            
        if not possible:
            continue
            
        for next_config in itertools.product(*agent_options):
            # Sort and merge duplicates
            unique_config = sorted(list(set(next_config)))
            next_state = tuple(unique_config)
            
            if next_state not in visited:
                visited.add(next_state)
                queue.append(next_state)
                
    print("Impossible")

if __name__ == "__main__":
    solve()
