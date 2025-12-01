from typing import Set, Tuple

def count_paths(n: int, forbidden: Set[Tuple[int,int]]) -> int:
    # dp[t][x][y] = ways to be at (x,y) after t steps
    # mode depends on t%4: 0,1 normal; 2,3 mirror
    size = n+1
    dp = [[[0]*(n+1) for _ in range(n+1)] for __ in range(2*n+1)]
    if (0,0) in forbidden:
        return 0
    dp[0][0][0] = 1
    for t in range(0, 2*n):
        mode = t % 4
        for x in range(0, n+1):
            for y in range(0, n+1):
                ways = dp[t][x][y]
                if ways == 0:
                    continue
                if (x,y) in forbidden:
                    continue
                # intended moves: Right and Up
                moves = [(1,0),(0,1)]
                for dx,dy in moves:
                    ndx, ndy = dx, dy
                    if mode in (2,3):  # mirror flips
                        ndx, ndy = dy, dx
                    nx, ny = x+ndx, y+ndy
                    if nx<0 or ny<0 or nx>n or ny>n:
                        continue
                    if (nx,ny) in forbidden:
                        continue
                    dp[t+1][nx][ny] += ways
    return dp[2*n][n][n]

if __name__ == "__main__":
    print(count_paths(3, {(1,2)}))  # Expected 4
