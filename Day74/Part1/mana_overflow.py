def solve():
    try:
        line = input().split()
        if not line:
            return
        
        # Parsing logic
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            gain = [int(x) for x in line2]
            line3 = input().split()
            M = int(line3[0])
            B = int(line3[1])
        else:
            # Maybe gain is first?
            # Let's assume standard: n, then gain, then M B
            # Or if line has multiple, it's gain?
            # If line has > 2 elements, it's gain.
            if len(line) > 2:
                gain = [int(x) for x in line]
                n = len(gain)
                line2 = input().split()
                M = int(line2[0])
                B = int(line2[1])
            else:
                n = int(line[0])
                line2 = input().split()
                gain = [int(x) for x in line2]
                line3 = input().split()
                M = int(line3[0])
                B = int(line3[1])

        possible = True
        for g in gain:
            M += g
            while M > B:
                M //= 2
            if M == 0:
                possible = False
                break
                
        print("1" if possible else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
