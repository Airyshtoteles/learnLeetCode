from collections import deque

def solve_hex_arena(hex_list):
    # hex_list: list of (q, r, char)
    grid = {}
    start_pos = None
    end_pos = None
    
    for q, r, char in hex_list:
        grid[(q, r)] = char
        if char == 'S':
            start_pos = (q, r)
        elif char == 'E':
            end_pos = (q, r)
            
    if not start_pos or not end_pos:
        return -1
        
    # BFS
    # State: (q, r, mask)
    queue = deque([(start_pos[0], start_pos[1], 0, 0)]) # q, r, mask, steps
    visited = set([(start_pos[0], start_pos[1], 0)])
    
    # Hex neighbors (Axial)
    # +q, -r | +q, 0 | 0, +r | -q, +r | -q, 0 | 0, -r ??
    # Standard Axial neighbors:
    # (1, 0), (1, -1), (0, -1), (-1, 0), (-1, 1), (0, 1)
    neighbors = [
        (1, 0), (1, -1), (0, -1),
        (-1, 0), (-1, 1), (0, 1)
    ]
    
    while queue:
        q, r, mask, steps = queue.popleft()
        
        if (q, r) == end_pos:
            return steps
            
        for dq, dr in neighbors:
            nq, nr = q + dq, r + dr
            
            if (nq, nr) in grid:
                cell = grid[(nq, nr)]
                
                if cell == '#':
                    continue
                    
                new_mask = mask
                is_passable = True
                
                # Check Barrier
                if 'A' <= cell <= 'J' and cell != 'E':
                    barrier_id = ord(cell) - ord('A')
                    if not (mask & (1 << barrier_id)):
                        is_passable = False
                        
                # Check Plate
                if 'a' <= cell <= 'j':
                    plate_id = ord(cell) - ord('a')
                    new_mask = mask ^ (1 << plate_id)
                    
                if is_passable:
                    if (nq, nr, new_mask) not in visited:
                        visited.add((nq, nr, new_mask))
                        queue.append((nq, nr, new_mask, steps + 1))
                        
    return -1

if __name__ == "__main__":
    # Example 1
    # S -> a -> A -> E
    # (0,0) S
    # (1,0) a (Plate 0)
    # (2,0) A (Barrier 0)
    # (3,0) E
    
    hexes = [
        (0, 0, 'S'),
        (1, 0, 'a'),
        (2, 0, 'A'),
        (3, 0, 'E')
    ]
    print(f"Min Steps (Ex 1): {solve_hex_arena(hexes)}")
    
    # Example 2: Blocked
    # S -> A -> E (No switch)
    hexes2 = [
        (0, 0, 'S'),
        (1, 0, 'A'),
        (2, 0, 'E')
    ]
    print(f"Min Steps (Ex 2): {solve_hex_arena(hexes2)}")
