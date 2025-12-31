import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        Start = int(next(iterator))
        Target = int(next(iterator))
        
        a = [0] * (N + 1)
        for i in range(1, N + 1):
            a[i] = int(next(iterator))
            
        edges = []
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            cost = int(next(iterator))
            edges.append((u, v, cost))
    except StopIteration:
        return

    INF = float('inf')
    dist = [-INF] * (N + 1)
    dist[Start] = 0
    
    # N-1 iterations
    for _ in range(N - 1):
        for u, v, cost in edges:
            if dist[u] != -INF:
                new_val = dist[u] + a[v] - cost
                if new_val > dist[v]:
                    dist[v] = new_val
                    
    # Check for positive cycles
    # Propagate infinity
    for _ in range(N):
        updated = False
        for u, v, cost in edges:
            if dist[u] != -INF:
                new_val = dist[u] + a[v] - cost
                if new_val > dist[v]:
                    dist[v] = INF
                    updated = True
                if dist[u] == INF:
                    if dist[v] != INF:
                        dist[v] = INF
                        updated = True
        if not updated:
            break
            
    if dist[Target] == INF:
        print("true")
    else:
        print("false")

if __name__ == "__main__":
    solve()
