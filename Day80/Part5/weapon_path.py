import sys
import heapq

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        S = int(next(iterator))
        E = int(next(iterator))
        InitDur = int(next(iterator))
        
        adj = [[] for _ in range(N + 1)]
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            w = int(next(iterator))
            adj[u].append((v, w))
            adj[v].append((u, w))
    except StopIteration:
        return

    # Max heap: store (-durability, u, repaired)
    pq = [(-InitDur, S, 0)]
    
    # max_dur[u][repaired]
    max_dur = [[-1] * 2 for _ in range(N + 1)]
    max_dur[S][0] = InitDur
    
    while pq:
        d_neg, u, r = heapq.heappop(pq)
        d = -d_neg
        
        if d < max_dur[u][r]:
            continue
        
        if u == E:
            print("true")
            return
        
        # Option 1: Move
        for v, w in adj[u]:
            new_d = d - w
            if new_d >= 0:
                if new_d > max_dur[v][r]:
                    max_dur[v][r] = new_d
                    heapq.heappush(pq, (-new_d, v, r))
                    
        # Option 2: Repair
        if r == 0:
            new_d = InitDur
            if new_d > max_dur[u][1]:
                max_dur[u][1] = new_d
                heapq.heappush(pq, (-new_d, u, 1))
                
    print("false")

if __name__ == "__main__":
    solve()
