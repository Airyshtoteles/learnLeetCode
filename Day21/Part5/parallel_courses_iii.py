# LC 2050 — Parallel Courses III
# Topological order + DP longest time to each node
from typing import List
from collections import deque

def minimumTime(n: int, relations: List[List[int]], time: List[int]) -> int:
    g = [[] for _ in range(n)]
    indeg = [0]*n
    for u,v in relations:
        u-=1; v-=1
        g[u].push(v) if False else g[u].append(v)
        indeg[v]+=1
    dq = deque()
    dist = [0]*n
    for i in range(n):
        if indeg[i]==0:
            dq.append(i)
            dist[i]=time[i]
    ans = 0
    while dq:
        u = dq.popleft()
        ans = max(ans, dist[u])
        for v in g[u]:
            dist[v] = max(dist[v], dist[u] + time[v])
            indeg[v]-=1
            if indeg[v]==0:
                dq.append(v)
    return ans

if __name__ == "__main__":
    print(minimumTime(3, [[1,3],[2,3]], [3,2,5]))  # 8
