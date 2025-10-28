# LC 664 — Strange Printer
# Interval DP: dp[i][j] = min turns to print s[i..j]

from functools import lru_cache

def strangePrinter(s: str) -> int:
    if not s:
        return 0
    # compress consecutive duplicates
    t = []
    for ch in s:
        if not t or t[-1] != ch:
            t.append(ch)
    s = ''.join(t)
    n = len(s)

    @lru_cache(None)
    def dp(i: int, j: int) -> int:
        if i > j:
            return 0
        if i == j:
            return 1
        res = dp(i+1, j) + 1
        for k in range(i+1, j+1):
            if s[i] == s[k]:
                res = min(res, dp(i+1, k-1) + dp(k, j))
        return res

    return dp(0, n-1)

if __name__ == "__main__":
    print(strangePrinter("aba"))  # 2
