def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            d = [int(x) for x in line2]
            line3 = input().split()
            H = int(line3[0])
        else:
            if len(line) > 2:
                d = [int(x) for x in line]
                n = len(d)
                line2 = input().split()
                H = int(line2[0])
            else:
                n = int(line[0])
                line2 = input().split()
                d = [int(x) for x in line2]
                line3 = input().split()
                H = int(line3[0])
                
        # Subset sum
        sums = {0}
        for x in d:
            new_sums = set()
            for s in sums:
                new_sums.add(s + x)
            sums.update(new_sums)
            
        found = False
        for s in sums:
            if s > 0 and H % s == 0:
                found = True
                break
                
        print("1" if found else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
