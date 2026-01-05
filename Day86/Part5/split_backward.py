import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = int(line1[0]), int(line1[1])
        
        rev_adj = collections.defaultdict(list)
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            # Edge u -> v. We traverse v -> u.
            rev_adj[v].append(u)
            
        line_st = sys.stdin.readline().split()
        if not line_st: return
        Start, Target = int(line_st[0]), int(line_st[1])
    except ValueError:
        return

    # BFS from Start in Reverse Graph
    queue = collections.deque([Start])
    visited = {Start}
    
    while queue:
        u = queue.popleft()
        
        if u == Target:
            print("Possible")
            return
            
        for v in rev_adj[u]:
            if v not in visited:
                visited.add(v)
                queue.append(v)
                
    print("Impossible")

if __name__ == "__main__":
    solve()
