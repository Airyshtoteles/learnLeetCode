import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M = int(line1[0]), int(line1[1])
        
        parents = collections.defaultdict(list)
        for _ in range(M):
            u, v = map(int, sys.stdin.readline().split())
            # u -> v
            parents[v].append(u)
            
        line_t = sys.stdin.readline().split()
        if not line_t: return
        Target = int(line_t[0])
    except ValueError:
        return

    queue = collections.deque([Target])
    visited = {Target}
    
    while queue:
        u = queue.popleft()
        
        for p in parents[u]:
            if p in visited:
                print("Impossible")
                return
            visited.add(p)
            queue.append(p)
            
    print("Possible")

if __name__ == "__main__":
    solve()
