from typing import List, Tuple
from collections import defaultdict

def k_cover_lex_smallest(n: int, edges: List[Tuple[int,int]], k: int) -> List[int]:
    if k == 0:
        return []
    adj = [[] for _ in range(n)]
    deg = [0]*n
    for u,v in edges:
        adj[u].append(v)
        adj[v].append(u)
        deg[u]+=1; deg[v]+=1
    if any(d < k for d in deg):
        return []  # impossible
    selected = [False]*n
    contrib = [0]*n  # number of selected neighbors
    for v in range(n):
        # decide if selecting v helps any node not yet reaching k
        need_help = False
        for u in adj[v]:
            if contrib[u] < k:
                need_help = True
                break
        if not need_help and contrib[v] >= k:
            continue
        # select v
        selected[v] = True
        for u in adj[v]:
            contrib[u] += 1
        # self does not count (neighbors only)
    # Augment if still deficits
    for v in range(n):
        if contrib[v] < k:
            # pick all its neighbors explicitly
            for u in adj[v]:
                if not selected[u]:
                    selected[u] = True
                    for w in adj[u]:
                        contrib[w] += 1
            if contrib[v] < k:  # still not enough
                return []
    ans = [i for i,s in enumerate(selected) if s]
    return ans

if __name__ == "__main__":
    n=5
    edges=[(0,1),(1,2),(2,3),(3,4),(1,3),(0,2),(2,4)]
    print(k_cover_lex_smallest(n, edges, 2))
