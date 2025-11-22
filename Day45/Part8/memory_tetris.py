import copy

def solve():
    # Hardcoded Input
    # Width 6, Height 10
    # Pieces: I, I, O, T
    # Goal: Maximize lines
    
    W = 6
    H = 10
    pieces = ['I', 'I', 'O', 'T']
    
    # Shapes (Fixed orientation)
    shapes = {
        'I': [[1, 1, 1, 1]], # Flat I
        'O': [[1, 1], [1, 1]],
        'T': [[0, 1, 0], [1, 1, 1]],
        'L': [[0, 0, 1], [1, 1, 1]],
        'J': [[1, 0, 0], [1, 1, 1]],
        'S': [[0, 1, 1], [1, 1, 0]],
        'Z': [[1, 1, 0], [0, 1, 1]]
    }
    
    # Initial State: Empty Grid
    # Grid is list of lists, H rows, W cols. 0 is bottom.
    # Let's use 0 for empty, 1 for filled.
    initial_grid = [[0]*W for _ in range(H)]
    
    # Beam Search
    # List of (score, grid)
    beam = [(0, initial_grid)]
    BEAM_WIDTH = 20
    
    for p_type in pieces:
        shape = shapes[p_type]
        piece_h = len(shape)
        piece_w = len(shape[0])
        
        next_beam = []
        
        for score, grid in beam:
            # Try all columns
            for c in range(W - piece_w + 1):
                final_y = -1
                # Scan from top down to find lowest valid position
                for y in range(H - piece_h, -1, -1):
                    # Check if fits at y
                    fits = True
                    for r in range(piece_h):
                        for k in range(piece_w):
                            if shape[r][k] == 1:
                                by = y + (piece_h - 1 - r)
                                if by >= H or grid[by][c+k] == 1:
                                    fits = False; break
                        if not fits: break
                    
                    if fits:
                        final_y = y
                    else:
                        break
                
                if final_y != -1:
                    # Place it
                    new_grid = [row[:] for row in grid]
                    for r in range(piece_h):
                        for k in range(piece_w):
                            if shape[r][k] == 1:
                                by = final_y + (piece_h - 1 - r)
                                new_grid[by][c+k] = 1
                    
                    # Check lines
                    lines_cleared = []
                    for r in range(H):
                        if all(new_grid[r]):
                            lines_cleared.append(r)
                    
                    current_score = score + len(lines_cleared)
                    
                    if not lines_cleared:
                        next_beam.append((current_score, new_grid))
                    else:
                        # Corruption Logic: Clear line + line above (Heuristic)
                        rows_to_keep = []
                        cleared_set = set(lines_cleared)
                        
                        bonus_clears = 0
                        for r in lines_cleared:
                            if r + 1 < H and (r+1) not in cleared_set:
                                cleared_set.add(r+1)
                                bonus_clears += 1
                        
                        current_score += bonus_clears
                        
                        for r in range(H):
                            if r not in cleared_set:
                                rows_to_keep.append(new_grid[r])
                        
                        # Fill top with empty
                        while len(rows_to_keep) < H:
                            rows_to_keep.append([0]*W)
                            
                        next_beam.append((current_score, rows_to_keep))

        # Prune Beam
        # Sort by score desc
        next_beam.sort(key=lambda x: x[0], reverse=True)
        beam = next_beam[:BEAM_WIDTH]
        
    if not beam:
        return 0
    return beam[0][0]

if __name__ == "__main__":
    result = solve()
    print(f"Max lines cleared: {result}")
