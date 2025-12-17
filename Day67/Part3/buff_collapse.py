def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        power = list(map(int, input().split()))
        duration = list(map(int, input().split()))
        
        max_durations = {}
        for p, d in zip(power, duration):
            if p not in max_durations or d > max_durations[p]:
                max_durations[p] = d
                
        print(sum(max_durations.values()))
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
