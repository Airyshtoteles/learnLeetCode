def solve():
    try:
        line = input().split()
        if not line: return
        T = int(line[0])
        
        spawn = list(map(int, input().split()))
        
        max_spawn = -1
        skips = 0
        skip_next = False
        
        for i in range(T):
            if skip_next:
                skips += 1
                skip_next = False
                if spawn[i] > max_spawn:
                    max_spawn = spawn[i]
                continue
                
            if spawn[i] > max_spawn:
                max_spawn = spawn[i]
                skip_next = True
                
        print(skips)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
