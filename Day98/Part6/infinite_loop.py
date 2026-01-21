import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        Start = int(next(iterator))
        TargetVal = int(next(iterator)) # Assuming 'R' value
        
        edges = []
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            w = int(next(iterator))
            edges.append((u, v, w))
    except StopIteration:
        return

    # Bellman Ford for Longest Path
    dist = {i: -float('inf') for i in range(N+1)}
    dist[Start] = 0
    
    # Relax N times
    for _ in range(N):
        changed = False
        for u, v, w in edges:
            if dist[u] != -float('inf') and dist[u] + w > dist[v]:
                dist[v] = dist[u] + w
                changed = True
        if not changed:
            break
            
    # Check Positive Cycle (Step N+1)
    has_pos_cycle = False
    for u, v, w in edges:
        if dist[u] != -float('inf') and dist[u] + w > dist[v]:
            has_pos_cycle = True
            break
            
    if has_pos_cycle:
        # If we have positive cycle reachable from Start, we can get Infinite.
        # Assuming Infinite >= TargetVal
        print("YES")
    else:
        # Check max value
        max_dist = max(dist.values())
        if max_dist >= TargetVal:
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    solve()
