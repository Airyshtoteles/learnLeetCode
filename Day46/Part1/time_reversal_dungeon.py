import heapq
import sys

def solve():
    # Example Input (Hardcoded for demonstration)
    # Grid 4x4
    # Cost matrix
    costs = [
        [1, 5, 1, 1],
        [1, 5, 1, 5],
        [1, 1, 1, 5],
        [5, 5, 5, 1]
    ]
    # Trap matrix (1 = trap)
    traps = [
        [0, 0, 0, 0],
        [0, 0, 1, 0], # Trap at (1, 2)
        [0, 0, 0, 0],
        [0, 0, 0, 0]
    ]
    
    N = len(costs)
    M = len(costs[0])
    
    start_node = (0, 0)
    end_node = (N-1, M-1)
    
    # Find all traps
    trap_locations = []
    for r in range(N):
        for c in range(M):
            if traps[r][c] == 1:
                trap_locations.append((r, c))
                
    def dijkstra(start_pos):
        # Priority Queue: (cost, r, c)
        # Note: Starting cost is 0 because we are AT the start_pos.
        # We pay to ENTER a cell.
        pq = [(0, start_pos[0], start_pos[1])]
        dist = {} # (r,c) -> min_cost
        dist[start_pos] = 0
        
        while pq:
            d, r, c = heapq.heappop(pq)
            
            if d > dist.get((r, c), float('inf')):
                continue
            
            # Directions: Up, Down, Left, Right
            for dr, dc in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nr, nc = r + dr, c + dc
                
                if 0 <= nr < N and 0 <= nc < M:
                    new_cost = d + costs[nr][nc]
                    if new_cost < dist.get((nr, nc), float('inf')):
                        dist[(nr, nc)] = new_cost
                        heapq.heappush(pq, (new_cost, nr, nc))
        return dist

    # 1. Run from Start
    dists_from_start = dijkstra(start_node)
    
    if end_node not in dists_from_start:
        print("-1")
        return

    min_energy = dists_from_start[end_node]
    print(f"Cost from Start: {min_energy}")
    
    # 2. Run from each reachable Trap
    for trap in trap_locations:
        # Check if trap is reachable from Start
        # Actually, we need to check if trap is reachable from Start OR any other reachable trap.
        # But since the grid is connected (unless walls exist), if Start can reach End, it can likely reach Traps.
        # Let's check reachability from Start specifically.
        if trap in dists_from_start:
            print(f"Trap at {trap} is reachable. Resetting cost to 0 and continuing.")
            dists_from_trap = dijkstra(trap)
            if end_node in dists_from_trap:
                trap_cost = dists_from_trap[end_node]
                print(f"Cost from Trap {trap}: {trap_cost}")
                if trap_cost < min_energy:
                    min_energy = trap_cost
    
    print(f"Minimum Energy: {min_energy}")

if __name__ == "__main__":
    solve()
