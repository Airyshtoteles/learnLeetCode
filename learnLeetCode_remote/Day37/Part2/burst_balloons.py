from typing import List

def max_coins(nums: List[int]) -> int:
    val = [1] + nums + [1]
    n = len(val)
    dp = [[0]*n for _ in range(n)]
    for len_ in range(2, n):  # interval size
        for l in range(0, n - len_):
            r = l + len_
            best = 0
            for k in range(l+1, r):
                best = max(best, dp[l][k] + val[l]*val[k]*val[r] + dp[k][r])
            dp[l][r] = best
    return dp[0][n-1]

if __name__ == "__main__":
    print(max_coins([3,1,5,8]))  # Expected 167
