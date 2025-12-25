import collections

def solve():
    try:
        line = input().split()
        if not line:
            return
        
        n, D = int(line[0]), int(line[1])
        
        if n == 0:
            print("0")
            return
        if n == 1:
            print("1")
            return
            
        line2 = input().split()
        pos = [int(x) for x in line2]
        line3 = input().split()
        v = [int(x) for x in line3]
        
        q = collections.deque([(0, 0)])
        visited = {(0, 0)}
        reached = False
        
        while q and not reached:
            plat, t = q.popleft()
            
            if t > 10000:
                continue
                
            if plat == n - 1:
                reached = True
                break
                
            curr_pos = pos[plat] + v[plat] * t
            
            for next_plat in range(n):
                if next_plat == plat:
                    continue
                    
                next_pos = pos[next_plat] + v[next_plat] * t
                
                if abs(curr_pos - next_pos) <= D:
                    if (next_plat, t) not in visited:
                        visited.add((next_plat, t))
                        q.append((next_plat, t))
                        
            if (plat, t + 1) not in visited:
                visited.add((plat, t + 1))
                q.append((plat, t + 1))
                
        print("1" if reached else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
