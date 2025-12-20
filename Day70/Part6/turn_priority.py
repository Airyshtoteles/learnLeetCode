def solve():
    try:
        line1 = input().split()
        if not line1:
            return
        n = int(line1[0])
        
        line2 = input().split()
        priorities = [int(x) for x in line2]
        
        total_turns = 0
        for p in priorities:
            while p > 0:
                p //= 2
                total_turns += 1
                
        print(total_turns)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
