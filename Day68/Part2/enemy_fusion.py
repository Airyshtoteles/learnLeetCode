def solve():
    try:
        line = input().split()
        if not line: return
        n = int(line[0])
        
        if n == 0:
            print(0)
            return
            
        a = list(map(int, input().split()))
        
        # dp[i][j]
        dp = [[0] * n for _ in range(n)]
        
        for i in range(n):
            dp[i][i] = a[i]
            
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                dp[i][j] = float('inf')
                for k in range(i, j):
                    val = max(dp[i][k], dp[k+1][j]) + 1
                    if val < dp[i][j]:
                        dp[i][j] = val
                        
        print(dp[0][n-1])
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
