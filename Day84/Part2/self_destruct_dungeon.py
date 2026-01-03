import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = int(line1[0]), int(line1[1])
        
        adj = collections.defaultdict(list)
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            adj[u].append(v)
            adj[v].append(u)
            
        line_st = sys.stdin.readline().split()
        if not line_st: return
        Start, Target = int(line_st[0]), int(line_st[1])
    except ValueError:
        return

    if Start == Target:
        print("Possible")
        return

    queue = collections.deque([Start])
    visited = {Start}
    
    while queue:
        u = queue.popleft()
        if u == Target:
            print("Possible")
            return
            
        for v in adj[u]:
            if v not in visited:
                visited.add(v)
                queue.append(v)
                
    print("Impossible")

if __name__ == "__main__":
    solve()
