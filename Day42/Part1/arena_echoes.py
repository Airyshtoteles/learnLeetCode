from typing import List, Tuple, Dict
import heapq

# Practical Dijkstra over (node, attr) with pruning.
# Returns minimal total cost to reach node n-1 with attr=0 or -1 if not found.

def popcount(x: int) -> int:
    return x.bit_count()


def min_cost_to_zero_attr(n: int, edges: List[Tuple[int, int, int]]) -> int:
    adj: List[List[Tuple[int, int]]] = [[] for _ in range(n)]
    for u, v, a in edges:
        adj[u].append((v, a))

    # dist[node]: dict attr->best_cost
    dist: List[Dict[int, int]] = [dict() for _ in range(n)]
    best_node = [10**30] * n  # best cost reaching node with any attr

    CAP = 512
    MARGIN = 64 * 60  # allow states within this margin of the node's current best

    pq: List[Tuple[int, int, int]] = []  # (cost, node, attr)
    heapq.heappush(pq, (0, 0, 0))
    dist[0][0] = 0
    best_node[0] = 0

    while pq:
        cost, u, a = heapq.heappop(pq)
        if dist[u].get(a, 10**30) != cost:
            continue
        if u == n - 1 and a == 0:
            return cost
        for v, w in adj[u]:
            na = a ^ w
            ncost = cost + popcount(na)
            # pruning by node best
            if ncost > best_node[v] + MARGIN:
                continue
            prev = dist[v].get(na)
            if prev is None or ncost < prev:
                dist[v][na] = ncost
                if ncost < best_node[v]:
                    best_node[v] = ncost
                # cap dictionary size with soft pruning: if too big, drop worst entries
                if len(dist[v]) > CAP:
                    # remove entries with cost > best_node[v] + MARGIN
                    to_del = [key for key, val in dist[v].items() if val > best_node[v] + MARGIN]
                    for key in to_del:
                        if len(dist[v]) <= CAP:
                            break
                        del dist[v][key]
                heapq.heappush(pq, (ncost, v, na))
    return -1


if __name__ == "__main__":
    n = 3
    edges = [(0, 1, 3), (1, 2, 1), (0, 2, 2)]
    print(min_cost_to_zero_attr(n, edges))  # -1 for example
