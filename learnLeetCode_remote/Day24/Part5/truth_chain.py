# The Truth Chain
# Master of Truth: trusts nobody (outdegree 0) and is trusted (transitively) by everyone else.
# Approach: build reverse graph; candidate must have outdeg 0 in original, and from candidate in reversed graph we can reach all nodes.
from typing import List, Tuple
from collections import defaultdict, deque

def master_of_truth(n: int, trust: List[Tuple[int,int]]) -> int:
    g = [[] for _ in range(n)]
    gr = [[] for _ in range(n)]
    outdeg = [0]*n
    for a,b in trust:
        a-=1; b-=1
        g[a].append(b)
        gr[b].append(a)
        outdeg[a]+=1
    # candidates: outdeg==0
    cand = [i for i in range(n) if outdeg[i]==0]
    for c in cand:
        # BFS from c in reversed graph -> nodes that can reach c in original
        vis = [False]*n
        dq = deque([c])
        vis[c]=True
        seen = 1
        while dq:
            u = dq.popleft()
            for v in gr[u]:
                if not vis[v]:
                    vis[v]=True; seen+=1; dq.append(v)
        if seen==n:
            return c+1
    return -1

if __name__ == "__main__":
    n=4; trust=[(1,3),(2,3),(3,4)]
    print(master_of_truth(n, trust))  # 4
