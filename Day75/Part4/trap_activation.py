def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            t = [int(x) for x in line2]
        else:
            t = [int(x) for x in line]
            
        if not t:
            print(0)
            return
            
        max_active = 0
        current = 0
        
        for trap in t:
            if trap == 1:
                current += 1
                max_active = max(max_active, current)
            else:
                current = 0
                
        print(max_active)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
