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
            w = [int(x) for x in line3]
        else:
            d = [int(x) for x in line]
            n = len(d)
            line2 = input().split()
            w = [int(x) for x in line2]
            
        if n == 0:
            print(0)
            return
            
        d.sort(reverse=True)
        
        total = 0
        for i in range(0, n, 2):
            if i + 1 < n:
                total += d[i] + 2 * d[i + 1]
            else:
                total += d[i]
                
        print(total)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
