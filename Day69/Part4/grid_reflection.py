def solve():
    try:
        line = input().split()
        if not line: return
        N = int(line[0])
        r = int(line[1])
        c = int(line[2])
        dr = int(line[3])
        dc = int(line[4])
        k = int(line[5])
        
        visited = set()
        visited.add((r, c))
        
        for _ in range(k):
            nr = r + dr
            nc = c + dc
            
            hit_wall = False
            if nr < 0 or nr >= N:
                dr = -dr
                hit_wall = True
            if nc < 0 or nc >= N:
                dc = -dc
                hit_wall = True
                
            if hit_wall:
                nr = r + dr
                nc = c + dc
                
            r, c = nr, nc
            visited.add((r, c))
            
        print(len(visited))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
