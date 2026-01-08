import sys
from collections import deque
from itertools import product

# Recursion limit
sys.setrecursionlimit(2000)

def solve():
    try:
        line = sys.stdin.readline().split()
        if not line: return
        R, C = map(int, line)
        grid = [list(sys.stdin.readline().strip()) for _ in range(R)]
    except ValueError:
        return

    starts = []
    target = (R-1, C-1)
    
    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'S':
                starts.append((r, c))
                grid[r][c] = '.'
            elif grid[r][c] == 'T': # Explicit target support
                target = (r, c)
                grid[r][c] = '.'
                
    starts.sort()
    starts = tuple(starts)
    
    # Check bounds relative to grid (prevent issues)
    # Target R-1, C-1 default if not found?
    # Actually if 'T' is not found, assume BottomRight.
    
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    def is_adj(p1, p2):
        return abs(p1[0] - p2[0]) + abs(p1[1] - p2[1]) <= 1
        
    def get_outcomes(config):
        # Connected components
        k = len(config)
        visited = [False] * k
        comps = []
        for i in range(k):
            if not visited[i]:
                comp = []
                q = deque([i])
                visited[i] = True
                comp.append(i)
                while q:
                    u = q.popleft()
                    for v in range(k):
                        if not visited[v] and is_adj(config[u], config[v]):
                            visited[v] = True
                            q.append(v)
                            comp.append(v)
                comps.append(comp)
        
        # Choices per comp
        comp_choices = []
        for comp in comps:
            choices = sorted(list(set([config[i] for i in comp])))
            comp_choices.append(choices)
            
        outcomes = []
        for p in product(*comp_choices):
            t = tuple(sorted(list(p)))
            outcomes.append(t)
        return outcomes

    # BFS state builder
    transitions = {}
    visited_states = set()
    queue = deque([starts])
    visited_states.add(starts)
    
    LIMIT = 2000 # Safety
    
    while queue:
        if len(visited_states) > LIMIT: break
        curr = queue.popleft()
        
        if curr in transitions: continue
        
        valid_moves = []
        # Generate moves: product of directions for each clone
        # 4^k
        
        move_opts = []
        for p in curr:
            opts = []
            for i in range(4):
                nr, nc = p[0] + dr[i], p[1] + dc[i]
                if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#':
                    opts.append((nr, nc))
            move_opts.append(opts)
            
        # Cartesian of moves
        moves_list = [] # List of outcome lists
        move_products = list(product(*move_opts))
        
        # Optimization: Random sample if too many?
        # Or just break if too many?
        
        for mp in move_products:
            # mp is tuple of new positions (raw)
            # Adversary resolve
            outs = get_outcomes(mp)
            moves_list.append(outs)
            
            for out in outs:
                if out not in visited_states:
                    visited_states.add(out)
                    queue.append(out)
                    
        transitions[curr] = moves_list
        
    # Iteration
    win_set = set()
    all_states = list(visited_states)
    
    for s in all_states:
        for p in s:
            if p == target:
                win_set.add(s)
                break
                
    changed = True
    while changed:
        changed = False
        for s in all_states:
            if s in win_set: continue
            
            if s in transitions:
                can_win = False
                for outcomes in transitions[s]:
                    if not outcomes: continue
                    all_out = True
                    for out in outcomes:
                        if out not in win_set:
                            all_out = False
                            break
                    if all_out:
                        can_win = True
                        break
                if can_win:
                    win_set.add(s)
                    changed = True
                    
    if starts in win_set:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
