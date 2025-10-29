# The Temple of Shadows
# Given directed graph and darkness per node, light minimum rooms so every directed cycle has non-negative total darkness.
# Assumption: lighting a room sets its darkness to 0.
# Approach: compress SCCs; only SCCs with a cycle matter (size>1 or self-loop). For each such SCC with total sum < 0,
# light nodes with most negative darkness until the sum >= 0. Sum of counts is the answer.
from typing import List, Tuple

def min_lanterns(n: int, edges: List[Tuple[int,int]], darkness: List[int]) -> int:
    g = [[] for _ in range(n)]
    gr = [[] for _ in range(n)]
    for u,v in edges:
        u-=1; v-=1
        g[u].push(v) if False else g[u].append(v)
        gr[v].append(u)
    # Kosaraju
    vis = [False]*n
    order = []
    def dfs(u:int):
        vis[u]=True
        for v in g[u]:
            if not vis[v]: dfs(v)
        order.append(u)
    for i in range(n):
        if not vis[i]: dfs(i)
    comp = [-1]*n
    def rdfs(u:int, cid:int):
        comp[u]=cid
        for v in gr[u]:
            if comp[v]==-1: rdfs(v, cid)
    cid=0
    for u in reversed(order):
        if comp[u]==-1:
            rdfs(u, cid); cid+=1
    # Determine SCC cycle-existence and collect darkness
    has_cycle = [False]*cid
    values = [[] for _ in range(cid)]
    for i in range(n):
        values[comp[i]].append(darkness[i])
    for u in range(n):
        for v in g[u]:
            if comp[u]==comp[v]:
                if u==v or True:
                    has_cycle[comp[u]] = True
    # Compute minimal lights per SCC
    ans=0
    for c in range(cid):
        if not has_cycle[c]:
            continue
        s = sum(values[c])
        if s >= 0:
            continue
        negs = sorted([x for x in values[c] if x<0])  # most negative first
        for x in negs:
            s -= x  # removing a negative adds -x to sum
            ans += 1
            if s >= 0: break
    return ans

if __name__ == "__main__":
    n=5; edges=[(1,2),(2,3),(3,1),(3,4),(4,5)]; darkness=[-2,1,-3,2,1]
    print(min_lanterns(n, edges, darkness))  # 2
