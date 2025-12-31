import sys

# Max Flow (Dinic's Algorithm) implementation in Python
# To check if node connectivity > k

class Edge:
    def __init__(self, to, cap, rev):
        self.to = to
        self.cap = cap
        self.flow = 0
        self.rev = rev

def add_edge(adj, u, v, cap):
    adj[u].append(Edge(v, cap, len(adj[v])))
    adj[v].append(Edge(u, 0, len(adj[u]) - 1))

def bfs(adj, level, s, t):
    level[:] = [-1] * len(level)
    level[s] = 0
    q = [s]
    while q:
        u = q.pop(0)
        for edge in adj[u]:
            if edge.cap - edge.flow > 0 and level[edge.to] == -1:
                level[edge.to] = level[u] + 1
                q.append(edge.to)
    return level[t] != -1

def dfs(adj, level, ptr, u, t, pushed):
    if pushed == 0:
        return 0
    if u == t:
        return pushed
    for i in range(ptr[u], len(adj[u])):
        ptr[u] = i
        edge = adj[u][i]
        if level[u] + 1 != level[edge.to] or edge.cap - edge.flow == 0:
            continue
        tr = edge.to
        push = dfs(adj, level, ptr, tr, t, min(pushed, edge.cap - edge.flow))
        if push == 0:
            continue
        edge.flow += push
        adj[tr][edge.rev].flow -= push
        return push
    return 0

def dinic(adj, s, t):
    flow = 0
    level = [-1] * len(adj)
    while bfs(adj, level, s, t):
        ptr = [0] * len(adj)
        while True:
            pushed = dfs(adj, level, ptr, s, t, float('inf'))
            if pushed == 0:
                break
            flow += pushed
    return flow

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        R = int(next(iterator))
        C = int(next(iterator))
        k = int(next(iterator))
        grid = []
        for _ in range(R):
            grid.append(next(iterator))
    except StopIteration:
        return

    startR, startC = -1, -1
    targetR, targetC = -1, -1
    
    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'S':
                startR, startC = r, c
            elif grid[r][c] == 'T':
                targetR, targetC = r, c

    total_cells = R * C
    source = startR * C + startC
    sink = targetR * C + targetC + total_cells
    
    adj = [[] for _ in range(2 * total_cells)]
    
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    INF = float('inf')
    
    for r in range(R):
        for c in range(C):
            if grid[r][c] == '#':
                continue
                
            u_in = r * C + c
            u_out = u_in + total_cells
            
            cap = 1
            if (r == startR and c == startC) or (r == targetR and c == targetC):
                cap = INF
            
            add_edge(adj, u_in, u_out, cap)
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < R and 0 <= nc < C:
                    if grid[nr][nc] != '#':
                        v_in = nr * C + nc
                        add_edge(adj, u_out, v_in, INF)
                        
    max_flow = dinic(adj, source, sink)
    
    if max_flow > k:
        print("true")
    else:
        print("false")

if __name__ == "__main__":
    sys.setrecursionlimit(20000)
    solve()
