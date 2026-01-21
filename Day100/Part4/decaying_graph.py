import sys
import heapq

def solve():
    input_data = sys.stdin.read().split()
    if not input_data: return
    iterator = iter(input_data)
    
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        Q = int(next(iterator))
        
        adj = [[] for _ in range(N + 1)]
        # Directed assumption
        for _ in range(M):
            u = int(next(iterator))
            v = int(next(iterator))
            w = int(next(iterator))
            t = int(next(iterator))
            adj[u].append((v, w, t))
            adj[v].append((u, w, t)) # Undirected assumption for "weighted graph" typical
            
        for i in range(Q):
            u = int(next(iterator))
            v = int(next(iterator))
            t = int(next(iterator))
            
            # Dijkstra
            dist = {u: 0}
            pq = [(0, u)]
            
            found = False
            while pq:
                d, curr = heapq.heappop(pq)
                
                if d > dist.get(curr, float('inf')):
                    continue
                
                if curr == v:
                    print(d)
                    found = True
                    break
                
                for nv, nw, nt in adj[curr]:
                    if nt >= t:
                        nd = d + nw
                        if nd < dist.get(nv, float('inf')):
                            dist[nv] = nd
                            heapq.heappush(pq, (nd, nv))
                            
            if not found:
                print("-1")
                
    except StopIteration:
        pass

if __name__ == "__main__":
    solve()
