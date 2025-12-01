# LC 847 — Shortest Path Visiting All Nodes
# BFS with state (node, mask)
from collections import deque
from typing import List

def shortestPathLength(graph: List[List[int]]) -> int:
    n = len(graph)
    if n <= 1:
        return 0
    allmask = (1 << n) - 1
    q = deque()
    visited = [[False]*(1<<n) for _ in range(n)]
    for i in range(n):
        mask = 1 << i
        q.append((i, mask, 0))
        visited[i][mask] = True
    while q:
        u, mask, d = q.popleft()
        if mask == allmask:
            return d
        for v in graph[u]:
            nmask = mask | (1 << v)
            if not visited[v][nmask]:
                visited[v][nmask] = True
                q.append((v, nmask, d+1))
    return -1

if __name__ == "__main__":
    print(shortestPathLength([[1,2,3],[0],[0],[0]]))  # 4
