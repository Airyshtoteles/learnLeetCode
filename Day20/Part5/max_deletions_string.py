# LC 2430 — Maximum Deletions on a String
# DP + Z-function per suffix to get LCP(s[i:], s[i+k:]) = Z[k]

def z_function(t: str):
    n = len(t)
    z = [0]*n
    l = r = 0
    for i in range(1, n):
        if i <= r:
            z[i] = min(r - i + 1, z[i - l])
        while i + z[i] < n and t[z[i]] == t[i + z[i]]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l, r = i, i + z[i] - 1
    z[0] = n
    return z

def maximumDeletions(s: str) -> int:
    n = len(s)
    dp = [0]*(n+1)  # dp[i]: max deletions starting at i
    for i in range(n-1, -1, -1):
        best = 1  # can always take s[i:] as one piece if no further deletion possible
        t = s[i:]
        z = z_function(t)
        lim = (n - i)//2
        for k in range(1, lim+1):
            if z[k] >= k:
                best = max(best, 1 + dp[i + k])
        dp[i] = best
    return dp[0]

if __name__ == "__main__":
    print(maximumDeletions("abcabcdabc"))  # 2
