import sys
import bisect

# Fenwick Tree for frequency counting
class Fenwick:
    def __init__(self, size):
        self.tree = [0] * (size + 1)

    def add(self, idx, val):
        idx += 1 
        while idx < len(self.tree):
            self.tree[idx] += val
            idx += idx & (-idx)

    def query(self, idx):
        idx += 1
        s = 0
        while idx > 0:
            s += self.tree[idx]
            idx -= idx & (-idx)
        return s

class DSU:
    def __init__(self, n, ft):
        self.parent = list(range(n))
        self.birth = [-1] * n
        self.ft = ft

    def find(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def activate(self, i, t_idx):
        self.birth[i] = t_idx
        self.ft.add(t_idx, 1)

    def unite(self, i, j, t_idx):
        root_i = self.find(i)
        root_j = self.find(j)

        if root_i != root_j:
            # Remove old births
            self.ft.add(self.birth[root_i], -1)
            self.ft.add(self.birth[root_j], -1)

            # Merge
            self.parent[root_i] = root_j
            self.birth[root_j] = t_idx # New combined birth is NOW
            
            # Add new birth
            self.ft.add(t_idx, 1)
            return True
        return False

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        K = int(next(iterator))
        Q = int(next(iterator))
        
        queries = []
        all_times = set()
        for _ in range(Q):
            t = int(next(iterator))
            r = int(next(iterator))
            c = int(next(iterator))
            queries.append((t, r, c))
            all_times.add(t)
            
    except StopIteration:
        return

    sorted_times = sorted(list(all_times))
    time_map = {t: i for i, t in enumerate(sorted_times)}
    
    ft = Fenwick(len(sorted_times))
    dsu = DSU(N * M, ft)
    grid = [[False]*M for _ in range(N)]
    
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    for t, r, c in queries:
        # Assuming 1-based input
        r -= 1
        c -= 1
        
        t_idx = time_map[t]
        
        if 0 <= r < N and 0 <= c < M:
            if not grid[r][c]:
                grid[r][c] = True
                u = r * M + c
                dsu.activate(u, t_idx)
                
                for k in range(4):
                    nr, nc = r + dr[k], c + dc[k]
                    if 0 <= nr < N and 0 <= nc < M and grid[nr][nc]:
                        v = nr * M + nc
                        dsu.unite(u, v, t_idx)
        
        # Count valid
        target_t = t - K
        # We need sum of freqs for times <= target_t
        # Find index in sorted_times
        idx = bisect.bisect_right(sorted_times, target_t) - 1
        
        if idx < 0:
            print(0)
        else:
            print(ft.query(idx))

if __name__ == "__main__":
    solve()
