def solve():
    try:
        line = input().split()
        if not line:
            return
        
        # Parsing logic
        # Assuming: n d1 d2 ... dn A X
        # Or: n \n d... \n A X
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            d = [int(x) for x in line2]
            line3 = input().split()
            A = int(line3[0])
            X = int(line3[1])
        else:
            # Maybe d is first line?
            # Let's assume standard competitive format:
            # Line 1: n
            # Line 2: d array
            # Line 3: A X
            # But if line has multiple, maybe it's d?
            # Let's try to be robust.
            # If first line has > 2 elements, it's likely d (and n is implicit or omitted).
            if len(line) > 2:
                d = [int(x) for x in line]
                n = len(d)
                line2 = input().split()
                A = int(line2[0])
                X = int(line2[1])
            else:
                # n is first
                n = int(line[0])
                line2 = input().split()
                d = [int(x) for x in line2]
                line3 = input().split()
                A = int(line3[0])
                X = int(line3[1])

        if A <= 0:
            print("1")
            return
        if X <= 0:
            print("0")
            return
            
        d.sort(reverse=True)
        
        count = min(n, X)
        if count == 0:
            print("0")
            return
            
        total_damage = d[0]
        for i in range(1, count):
            total_damage += d[i] // 2
            
        if total_damage >= A:
            print("1")
        else:
            print("0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
