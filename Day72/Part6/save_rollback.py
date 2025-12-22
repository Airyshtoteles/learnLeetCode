def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            a = [int(x) for x in line2]
        else:
            a = [int(x) for x in line]
            n = len(a)
            
        if n == 0:
            print(0)
            return
            
        length = 1
        for i in range(n - 1):
            if a[i] < a[i+1]:
                length += 1
            else:
                break
                
        print(length)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
