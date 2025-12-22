def solve():
    try:
        line = input().split()
        if not line:
            return
        H = int(line[0])
        
        if H >= 0:
            print("1")
        else:
            print("0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
