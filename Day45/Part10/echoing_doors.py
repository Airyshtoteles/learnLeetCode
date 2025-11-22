import heapq

def solve():
    # Hardcoded Input
    # 3x3x1 Maze (2D effectively for demo)
    # S . D0
    # . # .
    # D1 . G
    
    # Doors:
    # D0 (ID 0): Initially Open. Effect: Toggles D1.
    # D1 (ID 1): Initially Closed. Effect: None.
    
    # Path: S -> D0 (Cost 1, Toggles D1 to Open) -> ... -> D1 (Open, Cost 1) -> G.
    # Total Cost: 2.
    
    X, Y, Z = 3, 3, 1
    grid = [
        ["S.0", ".#.", "1.G"] # 0 and 1 are doors
    ]
    # Z is 1, so grid[0] is the only layer.
    
    # Door Info
    # ID -> {initial: 1/0, effect_mask: int}
    doors = {
        0: {'initial': 1, 'effect': (1 << 1)}, # D0 toggles D1
        1: {'initial': 0, 'effect': 0}         # D1 toggles nothing
    }
    
    num_doors = 2
    
    start_pos = None
    goal_pos = None
    door_locs = {} # (x,y,z) -> id
    
    for z in range(Z):
        for y in range(Y):
            for x in range(X):
                char = grid[z][y][x]
                if char == 'S':
                    start_pos = (x, y, z)
                elif char == 'G':
                    goal_pos = (x, y, z)
                elif char.isdigit():
                    door_id = int(char)
                    door_locs[(x, y, z)] = door_id
                    
    # Initial Mask
    initial_mask = 0
    for d_id, info in doors.items():
        if info['initial']:
            initial_mask |= (1 << d_id)
            
    # Dijkstra
    # (cost, x, y, z, mask)
    pq = [(0, start_pos[0], start_pos[1], start_pos[2], initial_mask)]
    
    # Visited/Dist
    # Using dict for sparse
    dist = {}
    dist[(start_pos, initial_mask)] = 0
    
    moves = [
        (1,0,0), (-1,0,0),
        (0,1,0), (0,-1,0),
        (0,0,1), (0,0,-1)
    ]
    
    while pq:
        cost, x, y, z, mask = heapq.heappop(pq)
        
        if (x, y, z) == goal_pos:
            return cost
            
        if dist.get(((x,y,z), mask), float('inf')) < cost:
            continue
            
        for dx, dy, dz in moves:
            nx, ny, nz = x + dx, y + dy, z + dz
            
            if 0 <= nx < X and 0 <= ny < Y and 0 <= nz < Z:
                char = grid[nz][ny][nx]
                
                if char == '#':
                    continue
                
                new_cost = cost
                new_mask = mask
                
                # Check if door
                if (nx, ny, nz) in door_locs:
                    d_id = door_locs[(nx, ny, nz)]
                    # Check if open
                    if (mask >> d_id) & 1:
                        # Passable
                        new_cost += 1
                        # Effect
                        effect = doors[d_id]['effect']
                        new_mask ^= effect
                    else:
                        # Closed
                        continue
                else:
                    # Empty or S/G
                    new_cost += 0
                    
                state = ((nx, ny, nz), new_mask)
                if new_cost < dist.get(state, float('inf')):
                    dist[state] = new_cost
                    heapq.heappush(pq, (new_cost, nx, ny, nz, new_mask))
                    
    return -1

if __name__ == "__main__":
    result = solve()
    print(f"Minimum doors passed: {result}")
