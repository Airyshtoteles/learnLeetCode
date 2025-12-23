def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            t = [int(x) for x in line2]
        else:
            t = [int(x) for x in line]
            n = len(t)
            
        if n == 0:
            print(0)
            return
            
        if n <= 2:
            print(max(t))
            return
            
        fixed_max = max(t[0], t[-1])
        
        middle = t[1:-1]
        if not middle:
            print(fixed_max)
            return
            
        # Find largest and second largest in middle
        # Or just sort middle
        middle.sort(reverse=True)
        
        # If we skip the largest (middle[0]), the new max is middle[1] if exists
        if len(middle) > 1:
            middle_max_after_skip = middle[1]
        else:
            middle_max_after_skip = 0
            
        print(max(fixed_max, middle_max_after_skip))
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
