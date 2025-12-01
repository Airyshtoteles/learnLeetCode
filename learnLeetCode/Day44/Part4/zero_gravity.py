import collections

def solve():
    # Hardcoded Input
    N = 4
    # Boxes: ID 1 is first.
    # Format: (ID, x, y, z)
    # Let's just store (x, y, z) in a list where index 0 is Box 1.
    initial_boxes = [
        (0, 0, 0), # Box 1
        (0, 0, 1), # Box 2
        (1, 0, 0)  # Box 3
    ]
    target = (3, 3, 3)
    
    # BFS
    # State: tuple of (x, y, z)
    start_state = tuple(initial_boxes)
    
    queue = collections.deque()
    queue.append((start_state, 0))
    
    visited = set()
    visited.add(start_state)
    
    # Directions: (dx, dy, dz, sort_axis, reverse_sort)
    # +x: dx=1. Sort by x desc (reverse=True).
    # -x: dx=-1. Sort by x asc (reverse=False).
    moves = [
        (1, 0, 0, 0, True),  # +x
        (-1, 0, 0, 0, False), # -x
        (0, 1, 0, 1, True),  # +y
        (0, -1, 0, 1, False), # -y
        (0, 0, 1, 2, True),  # +z
        (0, 0, -1, 2, False)  # -z
    ]
    
    while queue:
        current_boxes, steps = queue.popleft()
        
        # Check target (Box 1 is index 0)
        if current_boxes[0] == target:
            print(f"Minimum gravity changes: {steps}")
            return
        
        # Try all 6 directions
        for dx, dy, dz, axis, rev in moves:
            # Create a list of (index, box) to sort
            indexed_boxes = list(enumerate(current_boxes))
            
            # Sort
            indexed_boxes.sort(key=lambda p: p[1][axis], reverse=rev)
            
            # Simulation
            new_positions = list(current_boxes) # Copy
            occupied = set(current_boxes)
            
            changed = False
            
            for idx, (bx, by, bz) in indexed_boxes:
                occupied.remove((bx, by, bz))
                
                cx, cy, cz = bx, by, bz
                while True:
                    nx, ny, nz = cx + dx, cy + dy, cz + dz
                    if 0 <= nx < N and 0 <= ny < N and 0 <= nz < N and (nx, ny, nz) not in occupied:
                        cx, cy, cz = nx, ny, nz
                    else:
                        break
                
                if (cx, cy, cz) != (bx, by, bz):
                    changed = True
                
                new_positions[idx] = (cx, cy, cz)
                occupied.add((cx, cy, cz))
            
            if changed:
                new_state = tuple(new_positions)
                if new_state not in visited:
                    visited.add(new_state)
                    queue.append((new_state, steps + 1))
                    
    print("-1")

if __name__ == "__main__":
    solve()
