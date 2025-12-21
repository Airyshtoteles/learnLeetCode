def solve():
    try:
        line1 = input().split()
        if not line1:
            return
        H = int(line1[0])
        
        line2 = input().split()
        heals = [int(x) for x in line2]
        
        current_hp = H
        for h in heals:
            if h > 0:
                current_hp += h
                
        print(current_hp)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
