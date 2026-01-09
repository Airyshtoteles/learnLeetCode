import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = int(line1[0]), int(line1[1])
        
        adj = collections.defaultdict(list)
        rev_adj = collections.defaultdict(list)
        out_degree = collections.defaultdict(int)
        
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            rev_adj[v].append(u)
            out_degree[u] += 1
            
        line_st = sys.stdin.readline().split()
        if not line_st: return
        Start, Target = int(line_st[0]), int(line_st[1])
    except ValueError:
        return

    if Start == Target:
        print("Possible")
        return

    winning = {Target}
    safe_edges = collections.defaultdict(int)
    queue = collections.deque([Target])
    
    while queue:
        u = queue.popleft()
        
        for v in rev_adj[u]:
            if v in winning: continue
            
            safe_edges[v] += 1
            if safe_edges[v] == out_degree[v]:
                winning.add(v)
                queue.append(v)
                
    if Start in winning:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
