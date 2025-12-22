def solve():
    try:
        line = input().split()
        if not line:
            return
        
        # Input format: n, then pos line, then dir line?
        # Or just pos line, dir line?
        # Assuming n is first.
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            pos = [int(x) for x in line2]
            line3 = input().split()
            dirs = [int(x) for x in line3]
        else:
            # Maybe just pos and dir? But usually n is given.
            # Let's assume standard competitive format.
            # If line has multiple, maybe it's pos?
            # Let's try to parse robustly.
            # If first line is just one number, it's n.
            # If first line is array, it's pos.
            pos = [int(x) for x in line]
            n = len(pos)
            line2 = input().split()
            dirs = [int(x) for x in line2]
            
        npcs = []
        for i in range(n):
            npcs.append((pos[i], dirs[i]))
            
        # Sort by position
        npcs.sort(key=lambda x: x[0])
        
        collisions = 0
        rights = 0
        
        for p, d in npcs:
            if d == 1:
                rights += 1
            else:
                collisions += rights
                
        print(collisions)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
