# LC 2328 — Number of Increasing Paths in a Grid
from typing import List
import sys
sys.setrecursionlimit(1 << 25)

MOD = 10**9 + 7

def countPaths(grid: List[List[int]]) -> int:
    m, n = len(grid), len(grid[0])
    memo = [[-1]*n for _ in range(m)]
    DIRS = [(1,0),(-1,0),(0,1),(0,-1)]

    def dfs(x: int, y: int) -> int:
        if memo[x][y] != -1:
            return memo[x][y]
        res = 1  # path of length 1 (cell itself)
        for dx, dy in DIRS:
            nx, ny = x+dx, y+dy
            if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] > grid[x][y]:
                res += dfs(nx, ny)
                if res >= 1<<63: # avoid Python int blow? not needed, but keep mod small
                    res %= MOD
        res %= MOD
        memo[x][y] = res
        return res

    ans = 0
    for i in range(m):
        for j in range(n):
            ans = (ans + dfs(i, j)) % MOD
    return ans

if __name__ == "__main__":
    print(countPaths([[1,2],[3,4]]))  # 8
