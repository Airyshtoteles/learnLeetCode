import heapq
import sys

def solve():
    # Hardcoded Input
    N = 5
    # Edges: (u, v, weight, k)
    # k=1 means normal edge. k>1 means rotating bridge.
    edges = [
        (0, 1, 5, 1),   # Normal, weight 5
        (1, 2, 2, 3),   # Rotating, period 3, weight 2
        (2, 3, 4, 1),
        (0, 3, 15, 1),
        (3, 4, 3, 5)    # Rotating, period 5, weight 3
    ]
    
    # Monsters: (node, deadline)
    monsters = [
        (2, 20),
        (4, 30)
    ]
    
    adj = [[] for _ in range(N)]
    for u, v, w, k in edges:
        adj[u].append((v, w, k))
        adj[v].append((u, w, k))
        
    def dijkstra(start_node, start_time, target_node=None):
        # Returns min time to reach all nodes (or target)
        dist = {} # Use dict for sparse or just array
        dist = [float('inf')] * N
        dist[start_node] = start_time
        
        pq = [(start_time, start_node)]
        
        while pq:
            t, u = heapq.heappop(pq)
            
            if t > dist[u]:
                continue
            
            if target_node is not None and u == target_node:
                return t
            
            for v, w, k in adj[u]:
                # Calculate wait
                # Must leave u at time T such that T % k == 0
                # We arrived at t.
                # Next multiple of k >= t
                if t % k == 0:
                    wait = 0
                else:
                    wait = k - (t % k)
                
                arrival = t + wait + w
                
                if arrival < dist[v]:
                    dist[v] = arrival
                    heapq.heappush(pq, (arrival, v))
                    
        if target_node is not None:
            return float('inf')
        return dist

    # 1. Start -> Monsters
    # We can run one Dijkstra from Start to get times to all monsters
    to_monsters = dijkstra(0, 0)
    
    max_time_needed = 0
    
    for m_node, deadline in monsters:
        arrival_at_m = to_monsters[m_node]
        
        if arrival_at_m == float('inf'):
            print("-1") # Unreachable
            return
            
        # 2. Monster -> Start
        # Must run new Dijkstra because start_time matters for modulo
        back_to_start = dijkstra(m_node, arrival_at_m, 0)
        
        if back_to_start == float('inf'):
            print("-1")
            return
            
        total_time = back_to_start
        
        if total_time > deadline:
            print("-1") # Deadline missed
            return
            
        max_time_needed = max(max_time_needed, total_time)
        
    print(f"Minimum Time: {max_time_needed}")

if __name__ == "__main__":
    solve()
