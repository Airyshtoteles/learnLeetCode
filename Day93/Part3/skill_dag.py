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
        K = int(next(iterator))
        T = int(next(iterator))
    except StopIteration:
        return

    adj = [[] for _ in range(N + 1)]
    in_degree = [0] * (N + 1)
    
    for _ in range(M):
        u = int(next(iterator))
        v = int(next(iterator))
        adj[u].append(v)
        in_degree[v] += 1
        
    queue = deque()
    min_dist = [10**9] * (N + 1)
    
    for i in range(1, N + 1):
        if in_degree[i] == 0:
            queue.append((i, 1))
            min_dist[i] = 1
            
    while queue:
        u, dist = queue.popleft()
        
        if u == T:
            if dist <= K:
                print("YES")
                return
        
        if dist >= K:
            continue
            
        for v in adj[u]:
            if min_dist[v] > dist + 1:
                min_dist[v] = dist + 1
                queue.append((v, dist + 1))
                
    print("NO")

if __name__ == "__main__":
    solve()
