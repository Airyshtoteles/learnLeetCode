import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        K_agents = int(next(iterator))
        T_delay = int(next(iterator))
        Limit = int(next(iterator))
        
        grid = []
        agents = []
        safe_cells = []
        for r in range(N):
            row = next(iterator)
            grid.append(row)
            for c in range(M):
                if row[c] == 'A':
                    agents.append((r, c))
                if row[c] != '#':
                    safe_cells.append((r, c))
                    
    except StopIteration:
        return

    if Limit < T_delay:
        print("NO")
        return

    # Map cells to IDs
    cell_to_id = {pos: i for i, pos in enumerate(safe_cells)}
    id_to_cell = {i: pos for i, pos in enumerate(safe_cells)}
    num_cells = len(safe_cells)
    
    # Distance Matrix
    # Use BFS from each cell? Python might be slow if num_cells is large.
    # N, M <= 20? If 50, 2500 BFS in Py is slow.
    # Assuming small constraints for Python.
    
    # Optimization: Only compute relevant distances?
    # We need Dist(Start -> Candidate) and Dist(Candidate -> Target).
    # Just compute APSP on the safe graph?
    
    adj = [[] for _ in range(num_cells)]
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    for u in range(num_cells):
        r, c = id_to_cell[u]
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if (nr, nc) in cell_to_id:
                v = cell_to_id[(nr, nc)]
                adj[u].append(v)
                
    # APSP - BFS from each node
    dist_matrix = [[999999] * num_cells for _ in range(num_cells)]
    
    for start_node in range(num_cells):
        dist_matrix[start_node][start_node] = 0
        q = deque([start_node])
        while q:
            u = q.popleft()
            d = dist_matrix[start_node][u]
            for v in adj[u]:
                if dist_matrix[start_node][v] > d + 1:
                    dist_matrix[start_node][v] = d + 1
                    q.append(v)
                    
    # Candidates
    agent_reach = []
    for k in range(min(K_agents, len(agents))):
        start_pos = agents[k]
        start_id = cell_to_id.get(start_pos)
        if start_id is None: # Should not happen
            agent_reach.append([])
            continue
            
        cands = []
        for u in range(num_cells):
            if dist_matrix[start_id][u] <= T_delay:
                cands.append(u)
        agent_reach.append(cands)
        
    # Greedy Set Cover
    radius = Limit - T_delay
    covered = [False] * num_cells
    covered_count = 0
    
    for k in range(min(K_agents, len(agents))):
        best_cand = -1
        best_gain = -1
        
        for cand in agent_reach[k]:
            gain = 0
            for target in range(num_cells):
                if not covered[target] and dist_matrix[cand][target] <= radius:
                    gain += 1
            if gain > best_gain:
                best_gain = gain
                best_cand = cand
                
        if best_cand != -1:
            for target in range(num_cells):
                if not covered[target] and dist_matrix[best_cand][target] <= radius:
                    covered[target] = True
                    covered_count += 1
                    
    if covered_count == num_cells:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
