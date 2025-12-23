def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            w = [int(x) for x in line2]
        else:
            w = [int(x) for x in line]
            n = len(w)
            
        if n == 0:
            print("1")
            return
            
        total = sum(w)
        if total % n == 0:
            print("1")
        else:
            print("0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
