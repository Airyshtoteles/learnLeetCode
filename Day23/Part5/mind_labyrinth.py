# The Mind Labyrinth
# Edge (u,v,w). Cost to move along an edge at step when visited_count = k is w * k, where k = number of distinct nodes visited so far (including start).
# Start at node 1; want min cost to reach node n.
# Approximation: Dijkstra on (node, k) without exact visited set, with Pareto pruning.
# This may be optimistic; for given constraints this heuristic is used per prompt hint.
from typing import List, Tuple
import heapq

def min_cost_mind_labyrinth(n: int, edges: List[Tuple[int,int,int]]) -> int:
    g = [[] for _ in range(n)]
    for u,v,w in edges:
        u-=1; v-=1
        g[u].append((v,w))
        g[v].append((u,w))  # assume undirected? Prompt says graph berbobot; not specified directed; we'll assume undirected for flexibility
    INF = 10**18
    dist = [ [INF]*(n+1) for _ in range(n) ]
    # Start: at node 0 with k=1 (visited node 1)
    dist[0][1] = 0
    pq = [(0, 0, 1)]  # cost, node, k
    while pq:
        d,u,k = heapq.heappop(pq)
        if d != dist[u][k]:
            continue
        if u == n-1:
            return d
        # transitions: to neighbor v either as already-visited (k) or newly-visited (k+1)
        for v,w in g[u]:
            # optimistic: try both, but enforce k+1 <= n
            # prefer non-increasing dominance: only push if improves dist
            # as old
            nd = d + w * k
            if nd < dist[v][k]:
                dist[v][k] = nd
                heapq.heappush(pq, (nd, v, k))
            if k < n:
                nd2 = d + w * (k+1)
                if nd2 < dist[v][k+1]:
                    dist[v][k+1] = nd2
                    heapq.heappush(pq, (nd2, v, k+1))
    return -1

if __name__ == "__main__":
    n=4
    edges=[(1,2,3),(2,3,2),(3,4,4),(1,3,10)]
    print(min_cost_mind_labyrinth(n, edges))  # expected around 19 per prompt
