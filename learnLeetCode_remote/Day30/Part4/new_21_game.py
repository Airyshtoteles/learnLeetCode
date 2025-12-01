from typing import List

def new21Game(n: int, k: int, maxPts: int) -> float:
    if k == 0 or n >= k - 1 + maxPts:
        return 1.0
    dp = [0.0] * (n + 1)
    dp[0] = 1.0
    window = 1.0  # sum of dp[i] for i in [x-maxPts, x-1] that are < k
    res = 0.0
    for x in range(1, n + 1):
        dp[x] = window / maxPts
        if x < k:
            window += dp[x]
        else:
            res += dp[x]
        if x - maxPts >= 0:
            if x - maxPts < k:
                window -= dp[x - maxPts]
    return res

if __name__ == "__main__":
    tests = [
        (10, 1, 10),
        (6, 1, 10),
        (21, 17, 10),
        (0, 0, 1),
    ]
    for n, k, m in tests:
        print((n, k, m), "->", new21Game(n, k, m))
