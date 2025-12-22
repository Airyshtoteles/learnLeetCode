def solve():
    try:
        line = input().split()
        if not line:
            return
        # Check if first token is n or array
        # Assuming standard format: n then array, or just array
        # If line has 1 element, likely n.
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            seeds = [int(x) for x in line2]
        else:
            seeds = [int(x) for x in line]
            
        if not seeds:
            print(0)
            return
            
        dp = {}
        global_max = 0
        
        for x in seeds:
            current_max = 0
            # Find divisors
            # Optimization: iterate up to sqrt(x)
            i = 1
            while i * i <= x:
                if x % i == 0:
                    d1 = i
                    d2 = x // i
                    
                    if d1 in dp:
                        current_max = max(current_max, dp[d1])
                    if d2 in dp:
                        current_max = max(current_max, dp[d2])
                i += 1
            
            dp[x] = current_max + 1
            global_max = max(global_max, dp[x])
            
        print(global_max)
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
