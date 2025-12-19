def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        m = int(line[1])
        
        # Consume edges
        for _ in range(m):
            input()
            
        d = list(map(int, input().split()))
        
        if not d:
            print(0)
        else:
            print(max(d))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
