def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        c = list(map(int, input().split()))
        
        print(sum(c))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
