import sys
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M_edges = int(next(iterator))
        CurrentW = int(next(iterator))
        TargetW = int(next(iterator))
        StartNode = int(next(iterator))
        CoolSteps = int(next(iterator))
        
        Gain = []
        for _ in range(N):
            Gain.append(int(next(iterator)))
            
        adj = [[] for _ in range(N)]
        for _ in range(M_edges):
            u = int(next(iterator))
            v = int(next(iterator))
            adj[u].append(v)
            
    except StopIteration:
        return

    # Dijkstra Max Heap (-money)
    # State: (money, u, cds_tuple)
    
    init_cds = tuple([0] * N)
    pq = [(-CurrentW, StartNode, init_cds)]
    
    best_money = {} # (u, cds) -> max_money
    best_money[(StartNode, init_cds)] = CurrentW
    
    while pq:
        neg_m, u, cds = heapq.heappop(pq)
        money = -neg_m
        
        if money >= TargetW:
            print("YES")
            return
            
        if best_money.get((u, cds), -1) > money:
            continue
            
        # 1. Action: Execute transaction v (neighbor)
        for v in adj[u]:
            if cds[v] == 0:
                nxt_m = money + Gain[v]
                if nxt_m < 0:
                    continue
                
                # Decay
                temp_cds = [max(0, x - 1) for x in cds]
                
                # Apply Cooldown to v's neighbors (and v)
                temp_cds[v] = max(temp_cds[v], CoolSteps)
                for nbr in adj[v]:
                    temp_cds[nbr] = max(temp_cds[nbr], CoolSteps)
                    
                nxt_cds = tuple(temp_cds)
                
                if best_money.get((v, nxt_cds), -1) < nxt_m:
                    best_money[(v, nxt_cds)] = nxt_m
                    heapq.heappush(pq, (-nxt_m, v, nxt_cds))
                    
        # 2. Action: Wait (Decay Cooldowns)
        if any(x > 0 for x in cds):
            waited_cds = tuple([max(0, x - 1) for x in cds])
            if best_money.get((u, waited_cds), -1) < money:
                best_money[(u, waited_cds)] = money
                heapq.heappush(pq, (-money, u, waited_cds))
                
    print("NO")

if __name__ == "__main__":
    solve()
