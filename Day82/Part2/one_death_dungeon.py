import sys
import heapq
from collections import deque, defaultdict

def add_edge(adj, u, v, cap):
    adj[u].append([v, cap, len(adj[v])])
    adj[v].append([u, cap, len(adj[u]) - 1])

def bfs(adj, s, t):
    level = [-1] * len(adj)
    level[s] = 0
    q = deque([s])
    while q:
        v = q.popleft()
        for edge in adj[v]:
            if edge[1] > 0 and level[edge[0]] == -1:
                level[edge[0]] = level[v] + 1
                q.append(edge[0])
    return level if level[t] != -1 else None

def dfs(adj, level, v, t, pushed, ptr):
    if pushed == 0:
        return 0
    if v == t:
        return pushed
    while ptr[v] < len(adj[v]):
        edge_idx = ptr[v]
        to, cap, rev_idx = adj[v][edge_idx]
        if level[v] + 1 == level[to] and cap > 0:
            push = dfs(adj, level, to, t, min(pushed, cap), ptr)
            if push > 0:
                adj[v][edge_idx][1] -= push
                adj[to][rev_idx][1] += push
                return push
        ptr[v] += 1
    return 0

def dinic(adj, s, t):
    flow = 0
    while True:
        level = bfs(adj, s, t)
        if level is None:
            break
        ptr = [0] * len(adj)
        while True:
            pushed = dfs(adj, level, s, t, float('inf'), ptr)
            if pushed == 0:
                break
            flow += pushed
    return flow

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        V = int(next(iterator))
        E = int(next(iterator))
        S = int(next(iterator))
        T = int(next(iterator))
        
        adj = [[] for _ in range(V)]
        for _ in range(E):
            u = int(next(iterator))
            v = int(next(iterator))
            cap = int(next(iterator))
            add_edge(adj, u, v, cap)
            add_edge(adj, v, u, cap)
    except StopIteration:
        return

    max_flow = dinic(adj, S, T)

    if max_flow >= 2:
        print("true")
    else:
        print("false")

if __name__ == "__main__":
    solve()
