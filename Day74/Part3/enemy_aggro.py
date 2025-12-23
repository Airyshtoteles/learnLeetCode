def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            t = [int(x) for x in line2]
            line3 = input().split()
            d = [int(x) for x in line3]
        else:
            # Maybe t is first?
            # Let's assume standard competitive format.
            # If line has multiple, it's t.
            if len(line) > 1:
                t = [int(x) for x in line]
                n = len(t)
                line2 = input().split()
                d = [int(x) for x in line2]
            else:
                n = int(line[0])
                line2 = input().split()
                t = [int(x) for x in line2]
                line3 = input().split()
                d = [int(x) for x in line3]
                
        if n == 0:
            print(0)
            return
            
        intervals = []
        for i in range(n):
            intervals.append((t[i], t[i] + d[i]))
            
        # Sort by end time
        intervals.sort(key=lambda x: x[1])
        
        count = 0
        last_end = -1
        
        for start, end in intervals:
            if start >= last_end:
                count += 1
                last_end = end
                
        print(count)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
