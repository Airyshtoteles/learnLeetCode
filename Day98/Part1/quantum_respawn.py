import sys
from collections import deque

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M_edges = int(next(iterator))
        Start = int(next(iterator))
        Boss = int(next(iterator))
        KeyCheckpoint = int(next(iterator))
        
        adj = [[] for _ in range(N + 1)]
        for _ in range(M_edges):
            u = int(next(iterator))
            v = int(next(iterator))
            adj[u].append(v)
            
        K = int(next(iterator))
        checkpoints = []
        for _ in range(K):
            checkpoints.append(int(next(iterator)))
            
    except StopIteration:
        return

    # Helper
    try:
        key_idx = checkpoints.index(KeyCheckpoint)
    except ValueError:
        print("NO")
        return

    # BFS State: (mask, current_u)
    # Mask is bitmask of available checkpoints
    
    init_mask = (1 << K) - 1
    queue = deque([(init_mask, Start)])
    visited = set([(init_mask, Start)])
    
    while queue:
        mask, u = queue.popleft()
        
        # Verify Key
        if not ((mask >> key_idx) & 1):
            continue
            
        if u == Boss:
            print("YES")
            return
            
        # 1. Walk
        for v in adj[u]:
            if (mask, v) not in visited:
                visited.add((mask, v))
                queue.append((mask, v))
                
        # 2. Respawn
        # Pick spawn_idx from mask
        # Pick sac_idx from mask (sac != spawn)
        # New state: (mask \ sac, checkpoints[spawn])
        
        # Optimization: To maximize reachability, we usually sacrifice ANY useless node.
        # But in BFS we explore all.
        # N, K usually small. K <= 10.
        
        for spawn_idx in range(K):
            if (mask >> spawn_idx) & 1:
                spawn_node = checkpoints[spawn_idx]
                
                for sac_idx in range(K):
                    if sac_idx != spawn_idx and ((mask >> sac_idx) & 1):
                        new_mask = mask & ~(1 << sac_idx)
                        
                        # Key Check
                        if (new_mask >> key_idx) & 1:
                            if (new_mask, spawn_node) not in visited:
                                visited.add((new_mask, spawn_node))
                                queue.append((new_mask, spawn_node))
                                
    print("NO")

if __name__ == "__main__":
    solve()
