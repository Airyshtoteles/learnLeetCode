import heapq

def solve_hex_arena(target, blocked, runes):
    tx, ty, tz = target
    blocked_set = set(tuple(b) for b in blocked)
    rune_set = set(tuple(r) for r in runes)
    runes_list = [tuple(r) for r in runes]
    
    # Directions in Cube Coordinates
    # x+y+z = 0
    directions = [
        (1, -1, 0), (1, 0, -1), (0, 1, -1),
        (-1, 1, 0), (-1, 0, 1), (0, -1, 1)
    ]
    
    pq = [(0, 0, 0, 0)] # cost, x, y, z
    dist = {}
    dist[(0, 0, 0)] = 0
    
    limit = 50
    
    while pq:
        cost, x, y, z = heapq.heappop(pq)
        
        if x == tx and y == ty and z == tz:
            return cost
        
        if cost > dist.get((x, y, z), float('inf')):
            continue
        
        # 1. Walk (Cost 1)
        for dx, dy, dz in directions:
            nx, ny, nz = x + dx, y + dy, z + dz
            if max(abs(nx), abs(ny), abs(nz)) <= limit and (nx, ny, nz) not in blocked_set:
                new_cost = cost + 1
                if new_cost < dist.get((nx, ny, nz), float('inf')):
                    dist[(nx, ny, nz)] = new_cost
                    heapq.heappush(pq, (new_cost, nx, ny, nz))
                    
        # 2. Blink (Cost 2)
        for dx, dy, dz in directions:
            nx, ny, nz = x + dx, y + dy, z + dz
            while max(abs(nx), abs(ny), abs(nz)) <= limit and (nx, ny, nz) not in blocked_set:
                new_cost = cost + 2
                if new_cost < dist.get((nx, ny, nz), float('inf')):
                    dist[(nx, ny, nz)] = new_cost
                    heapq.heappush(pq, (new_cost, nx, ny, nz))
                nx += dx
                ny += dy
                nz += dz
                
        # 3. Rune Teleport (Cost 1)
        if (x, y, z) in rune_set:
            for rx, ry, rz in runes_list:
                if (rx, ry, rz) == (x, y, z):
                    continue
                new_cost = cost + 1
                if new_cost < dist.get((rx, ry, rz), float('inf')):
                    dist[(rx, ry, rz)] = new_cost
                    heapq.heappush(pq, (new_cost, rx, ry, rz))
                    
    return -1

if __name__ == "__main__":
    Target = [0, -2, 2]
    Blocked = [[0, -1, 1]]
    Runes = [[1, -1, 0], [0, -2, 2]]
    
    result = solve_hex_arena(Target, Blocked, Runes)
    print(f"Minimum Cost: {result}")
