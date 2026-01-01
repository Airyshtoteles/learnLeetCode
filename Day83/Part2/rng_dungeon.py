import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        R, C = int(line1[0]), int(line1[1])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        A, B, M, X0 = int(line2[0]), int(line2[1]), int(line2[2]), int(line2[3])
    except ValueError:
        return

    # Generate all blocked cells
    blocked = set()
    visited_x = set()
    
    x = X0
    while x not in visited_x:
        visited_x.add(x)
        
        # Mapping
        r = (x // C) % R
        c = x % C
        
        blocked.add((r, c))
        
        x = (x * A + B) % M
    
    start = (0, 0)
    target = (R-1, C-1)
    
    if start in blocked or target in blocked:
        print("Impossible")
        return

    # BFS
    queue = [start]
    visited_bfs = {start}
    
    while queue:
        curr_r, curr_c = queue.pop(0)
        
        if (curr_r, curr_c) == target:
            print("Possible")
            return
        
        for dr, dc in [(0,1), (0,-1), (1,0), (-1,0)]:
            nr, nc = curr_r + dr, curr_c + dc
            
            if 0 <= nr < R and 0 <= nc < C:
                if (nr, nc) not in blocked and (nr, nc) not in visited_bfs:
                    visited_bfs.add((nr, nc))
                    queue.append((nr, nc))
                    
    print("Impossible")

if __name__ == "__main__":
    solve()
