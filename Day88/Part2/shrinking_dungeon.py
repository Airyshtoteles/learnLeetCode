import sys

# Max Flow (Dinic) implementation
class Dinic:
    def __init__(self, n):
        self.n = n
        self.graph = [[] for _ in range(n)]
        self.level = []

    def add_edge(self, u, v, capacity):
        self.graph[u].append([v, capacity, len(self.graph[v])])
        self.graph[v].append([u, 0, len(self.graph[u]) - 1])

    def bfs(self, s, t):
        self.level = [-1] * self.n
        self.level[s] = 0
        queue = [s]
        while queue:
            u = queue.pop(0)
            for v, cap, rev in self.graph[u]:
                if cap > 0 and self.level[v] < 0:
                    self.level[v] = self.level[u] + 1
                    queue.append(v)
        return self.level[t] >= 0

    def dfs(self, u, t, flow, ptr):
        if u == t or flow == 0:
            return flow
        for i in range(ptr[u], len(self.graph[u])):
            ptr[u] = i
            v, cap, rev = self.graph[u][i]
            if self.level[v] == self.level[u] + 1 and cap > 0:
                pushed = self.dfs(v, t, min(flow, cap), ptr)
                if pushed > 0:
                    self.graph[u][i][1] -= pushed
                    self.graph[v][rev][1] += pushed
                    return pushed
        return 0

    def max_flow(self, s, t):
        max_f = 0
        while self.bfs(s, t):
            ptr = [0] * self.n
            while True:
                pushed = self.dfs(s, t, float('inf'), ptr)
                if pushed == 0:
                    break
                max_f += pushed
        return max_f

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, B = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        StartR, StartC, TargetR, TargetC = map(int, line2)
    except ValueError:
        return

    num_cells = N * M
    S = StartR * M + StartC
    T = TargetR * M + TargetC
    
    # Nodes: 0..num_cells-1 (In), num_cells..2*num_cells-1 (Out)
    dinic = Dinic(2 * num_cells)
    
    for r in range(N):
        for c in range(M):
            u = r * M + c
            u_in = u
            u_out = u + num_cells
            
            # Vertex Capacity
            cap = float('inf') if u == S or u == T else 1
            dinic.add_edge(u_in, u_out, cap)
            
            # Neighbors
            dr = [0, 0, 1, -1]
            dc = [1, -1, 0, 0]
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < N and 0 <= nc < M:
                    v = nr * M + nc
                    v_in = v
                    # Edge u_out -> v_in
                    dinic.add_edge(u_out, v_in, float('inf'))

    flow = dinic.max_flow(S, T + num_cells) # Actually flow from S_in (which goes to S_out) to T_out? 
    # Yes, S_in -> S_out (inf) -> neighbors_in.
    # T_in -> T_out (inf). Flow collected at T_out.
    
    if flow > B:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
