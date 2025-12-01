from typing import List

# LC 2328 — Number of Increasing Paths in a Grid
# DFS + memoization, mod 1e9+7.

MOD = 10**9 + 7
DIRS = [(1,0),(-1,0),(0,1),(0,-1)]

def countPaths(grid: List[List[int]]) -> int:
    n, m = len(grid), len(grid[0])
    memo = [[-1]*m for _ in range(n)]

    def dfs(x: int, y: int) -> int:
        if memo[x][y] != -1:
            return memo[x][y]
        total = 1  # path consisting of cell itself
        for dx, dy in DIRS:
            nx, ny = x+dx, y+dy
            if 0 <= nx < n and 0 <= ny < m and grid[nx][ny] > grid[x][y]:
                total += dfs(nx, ny)
        total %= MOD
        memo[x][y] = total
        return total

    ans = 0
    for i in range(n):
        for j in range(m):
            ans = (ans + dfs(i, j)) % MOD
    return ans

if __name__ == "__main__":
    print(countPaths([[1,2],[3,4]]))  # 8
