from typing import List, Tuple
import sys
sys.setrecursionlimit(1 << 20)

def min_diff(n: int, edges: List[Tuple[int,int]], power: List[int]) -> int:
    g = [[] for _ in range(n)]
    for u,v in edges:
        u-=1; v-=1
        g[u].append(v); g[v].append(u)
    S = sum(power)
    sub = [0]*n
    seen = [False]*n
    ans = float('inf')
    def dfs(u: int, p: int):
        nonlocal ans
        seen[u] = True
        s = power[u]
        for v in g[u]:
            if v==p: continue
            dfs(v,u)
            s += sub[v]
            ans = min(ans, abs(S - 2*sub[v]))
        sub[u] = s
    dfs(0,-1)
    return int(ans)

if __name__ == "__main__":
    n = 5
    edges = [(1,2),(1,3),(3,4),(3,5)]
    power = [1,2,3,6,2]
    print(min_diff(n, edges, power))  # Expected 2
