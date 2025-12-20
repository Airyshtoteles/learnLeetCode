def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        t = list(map(int, input().split()))
        
        if len(t) == len(set(t)):
            print("True")
        else:
            print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
