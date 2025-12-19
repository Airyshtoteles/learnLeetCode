def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        jump = list(map(int, input().split()))
        
        visited = set()
        curr = 0
        
        while True:
            if curr >= n:
                print("EXIT")
                return
            if curr in visited:
                print("LOOP")
                return
            visited.add(curr)
            
            curr = curr + jump[curr]
            
            if curr < 0:
                print("EXIT")
                return
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
