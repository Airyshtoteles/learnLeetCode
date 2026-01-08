import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M_edges, M_bad = map(int, line1)
        
        Target = int(sys.stdin.readline())
        
        adj = collections.defaultdict(list)
        in_degree = collections.defaultdict(int)
        for _ in range(M_edges):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            in_degree[v] += 1
            
        bad = collections.defaultdict(set)
        for _ in range(M_bad):
            u, v = map(int, sys.stdin.readline().split())
            # Taking u disables v
            bad[u].add(v)
            
    except ValueError:
        return

    queue = collections.deque()
    
    # Verify roots
    has_roots = False
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            if i in bad[i]: continue
            
            disabled = set()
            for b in bad[i]: disabled.add(b)
            
            queue.append((i, disabled))
            has_roots = True
            
    # Visited state: (u, frozen_disabled) is optimal but memory heavy
    # Visited node is heuristic
    visited_node = set()
    
    while queue:
        u, disabled = queue.popleft()
        
        if u == Target:
            print("Possible")
            return
            
        if u in visited_node: continue
        visited_node.add(u)
        
        for v in adj[u]:
            if v in disabled: continue
            
            new_disabled = disabled.copy()
            for b in bad[v]: new_disabled.add(b)
            
            queue.append((v, new_disabled))
            
    print("Impossible")

if __name__ == "__main__":
    solve()
