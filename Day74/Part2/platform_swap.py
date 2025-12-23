def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            h = [int(x) for x in line2]
        else:
            h = [int(x) for x in line]
            n = len(h)
            
        if n == 0:
            print("1")
            return
            
        h.sort()
        
        possible = True
        for i in range(n - 1):
            if abs(h[i] - h[i+1]) > 1:
                possible = False
                break
                
        print("1" if possible else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
