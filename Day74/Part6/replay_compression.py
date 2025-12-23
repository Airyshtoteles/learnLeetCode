import sys

# Increase recursion depth
sys.setrecursionlimit(2000)

memo = {}

def solve_dp(s):
    if not s:
        return 0
    if len(s) == 1:
        return 1
    if s in memo:
        return memo[s]
    
    n = len(s)
    min_len = n
    
    # Split
    for k in range(1, n):
        min_len = min(min_len, solve_dp(s[:k]) + solve_dp(s[k:]))
        
    # Compress
    for L in range(1, n // 2 + 1):
        if n % L == 0:
            pattern = s[:L]
            if pattern * (n // L) == s:
                min_len = min(min_len, solve_dp(pattern))
                
    memo[s] = min_len
    return min_len

def solve():
    try:
        line = sys.stdin.read().split()
        if not line:
            return
        s = line[0]
        
        global memo
        memo = {}
        
        final_len = solve_dp(s)
        print(len(s) - final_len)
            
    except Exception:
        pass

if __name__ == "__main__":
    solve()
