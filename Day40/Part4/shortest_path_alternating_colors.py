from collections import deque
from typing import List, Tuple

RED, BLUE = 0, 1

def shortest_alternating_paths(n: int, red_edges: List[Tuple[int,int]], blue_edges: List[Tuple[int,int]]) -> List[int]:
    red_adj = [[] for _ in range(n)]
    blue_adj = [[] for _ in range(n)]
    for u, v in red_edges:
        red_adj[u].append(v)
    for u, v in blue_edges:
        blue_adj[u].append(v)

    dist = [[float('inf')] * 2 for _ in range(n)]  # dist[node][lastColor]
    dq = deque()
    # start from node 0 with both color options
    dist[0][RED] = dist[0][BLUE] = 0
    dq.append((0, RED))
    dq.append((0, BLUE))

    while dq:
        u, last = dq.popleft()
        d = dist[u][last]
        if last == RED:
            # must take BLUE next
            for v in blue_adj[u]:
                if d + 1 < dist[v][BLUE]:
                    dist[v][BLUE] = d + 1
                    dq.append((v, BLUE))
        else:
            # must take RED next
            for v in red_adj[u]:
                if d + 1 < dist[v][RED]:
                    dist[v][RED] = d + 1
                    dq.append((v, RED))

    ans = []
    for i in range(n):
        best = min(dist[i])
        ans.append(-1 if best == float('inf') else best)
    return ans


if __name__ == "__main__":
    print(shortest_alternating_paths(3, [(0,1),(1,2)], []))  # [0,1,2]
    print(shortest_alternating_paths(3, [(0,1)], [(1,2)]))    # [0,1,2]
