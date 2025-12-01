from typing import List

def max_tokens(grid: List[List[int]]) -> int:
    n = len(grid)
    if n == 0: return -1
    INF_NEG = -10**18
    dp = [[INF_NEG]*n for _ in range(n)]
    if grid[0][0] >= 0:
        dp[0][0] = grid[0][0]
    for i in range(n):
        for j in range(n):
            if i == 0 and j == 0:
                continue
            best = INF_NEG
            if i > 0 and dp[i-1][j] != INF_NEG and dp[i-1][j] + grid[i][j] >= 0:
                best = max(best, dp[i-1][j] + grid[i][j])
            if j > 0 and dp[i][j-1] != INF_NEG and dp[i][j-1] + grid[i][j] >= 0:
                best = max(best, dp[i][j-1] + grid[i][j])
            dp[i][j] = best
    return -1 if dp[n-1][n-1] == INF_NEG else dp[n-1][n-1]

if __name__ == "__main__":
    grid = [
        [1, -2, 3],
        [2, -1, 2],
        [1,  2, 1]
    ]
    print(max_tokens(grid))
