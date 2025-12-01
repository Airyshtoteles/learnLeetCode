import heapq
from typing import List, Tuple

def min_cost_with_energy(n: int, edges: List[Tuple[int,int,int,int]], E: int) -> int:
    g = [[] for _ in range(n)]
    pos_sum = 0
    for u,v,c,r in edges:
        g[u].append((v,c,r))
        g[v].append((u,c,r))
        if r>0: pos_sum += r
    cap = E + pos_sum
    cap = min(cap, 100000)  # guard

    INF = 10**18
    dist = [ [INF]*(cap+1) for _ in range(n) ]
    e0 = min(E, cap)
    dist[0][e0] = 0
    pq = [(0, 0, e0)]  # (cost, node, energy)

    while pq:
        cost, u, en = heapq.heappop(pq)
        if cost != dist[u][en]:
            continue
        if u == n-1:
            return cost
        for v,c,r in g[u]:
            if en < c:
                continue
            nen = en - c + r
            if nen > cap: nen = cap
            ncost = cost + c
            if ncost < dist[v][nen]:
                dist[v][nen] = ncost
                heapq.heappush(pq, (ncost, v, nen))
    return -1

if __name__ == "__main__":
    n = 4
    edges = [(0,1,4,2),(1,2,3,3),(2,3,5,5)]
    E = 3
    print(min_cost_with_energy(n, edges, E))  # Expected 7
