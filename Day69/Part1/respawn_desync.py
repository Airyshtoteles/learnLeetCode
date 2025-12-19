def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        r = list(map(int, input().split()))
        r.sort()
        
        current_time = 0
        total_time = 0
        
        for val in r:
            if val > current_time:
                current_time = val
            else:
                current_time += 1
            total_time += current_time
            
        print(total_time)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
