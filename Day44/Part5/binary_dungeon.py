import collections

def solve():
    # Hardcoded Input
    N = 5
    M = 6
    
    # Edges: (u, v, type)
    edges = [
        (0, 1, 1),
        (1, 2, 1),
        (2, 3, 0),
        (3, 4, 1),
        (0, 1, 0), # Parallel edge? Or another path. Let's say 0->1 type 0 exists.
        (1, 3, 1)
    ]
    
    # Constraints: -1=None, 0=Req 0, 1=Req 1
    constraints = [-1] * N
    constraints[2] = 0
    constraints[3] = 1
    
    start_node = 0
    goal_node = 4
    
    # Build Graph
    adj = collections.defaultdict(list)
    for u, v, w in edges:
        adj[u].append((v, w))
        adj[v].append((u, w)) # Undirected? Usually dungeon is undirected unless specified.
        # "Dungeon memiliki ruangan terhubung graf". Usually undirected.
        
    # BFS
    # State: (u, parity)
    # dist[u][parity]
    dist = [[-1] * 2 for _ in range(N)]
    
    queue = collections.deque()
    
    # Initial
    # Start at start_node with parity 0.
    # Check if start_node satisfies constraint 0?
    if constraints[start_node] != -1 and constraints[start_node] != 0:
        print("Start node blocked")
        return
        
    dist[start_node][0] = 0
    queue.append((start_node, 0))
    
    while queue:
        u, p = queue.popleft()
        
        if u == goal_node:
            print(f"Shortest path: {dist[u][p]}")
            return
        
        for v, w in adj[u]:
            next_p = p ^ w
            
            # Check constraint
            if constraints[v] != -1 and constraints[v] != next_p:
                continue
            
            if dist[v][next_p] == -1:
                dist[v][next_p] = dist[u][p] + 1
                queue.append((v, next_p))
                
    print("-1")

if __name__ == "__main__":
    solve()
