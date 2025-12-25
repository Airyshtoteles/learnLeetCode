def solve():
    try:
        line = input().split()
        if not line:
            return
        
        n, K, S = int(line[0]), int(line[1]), int(line[2])
        
        if n == 0:
            print("1")
            return
            
        line2 = input().split()
        p = [int(x) for x in line2]
        
        active_power = 0
        possible = True
        
        for power in p:
            active_power += power
            
            defeated = min(K, active_power)
            active_power -= defeated
            
            if active_power > S:
                possible = False
                break
                
        print("1" if possible else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
