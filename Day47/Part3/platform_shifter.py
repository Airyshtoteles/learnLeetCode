import heapq

def solve_platform_shifter(n, k, grid):
    # Dijkstra's Algorithm
    # Priority Queue stores: (cost, r, c)
    pq = [(0, 0, 0)]
    
    # Distances dictionary/grid initialized to infinity
    dist = {}
    dist[(0, 0)] = 0
    
    directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
    
    while pq:
        current_cost, r, c = heapq.heappop(pq)
        
        # If we reached the target
        if r == n - 1 and c == n - 1:
            return current_cost
        
        # Optimization: If we found a shorter path to this node already, skip
        if current_cost > dist.get((r, c), float('inf')):
            continue
        
        for dr, dc in directions:
            nr, nc = r + dr, c + dc
            
            if 0 <= nr < n and 0 <= nc < n:
                h_curr = grid[r][c]
                h_next = grid[nr][nc]
                
                move_cost = 1
                penalty = 0
                
                if h_next > h_curr + k:
                    penalty = h_next - (h_curr + k)
                
                total_move_cost = move_cost + penalty
                new_cost = current_cost + total_move_cost
                
                if new_cost < dist.get((nr, nc), float('inf')):
                    dist[(nr, nc)] = new_cost
                    heapq.heappush(pq, (new_cost, nr, nc))
                    
    return -1 # Should not happen if graph is connected

if __name__ == "__main__":
    N = 3
    K = 2
    Grid = [
        [0, 5, 10],
        [2, 3, 8],
        [10, 1, 9]
    ]
    
    result = solve_platform_shifter(N, K, Grid)
    print(f"Minimum Cost: {result}")
