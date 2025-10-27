# LC 1312 — Minimum Insertion Steps to Make a String Palindrome
# Answer = n - LPS length; LPS is LCS(s, reversed(s))

def minInsertions(s: str) -> int:
    t = s[::-1]
    n = len(s)
    # LCS dp
    dp = [0]*(n+1)
    for i in range(1, n+1):
        prev = 0
        for j in range(1, n+1):
            cur = dp[j]
            if s[i-1] == t[j-1]:
                dp[j] = prev + 1
            else:
                dp[j] = max(dp[j], dp[j-1])
            prev = cur
    lps = dp[n]
    return n - lps

if __name__ == "__main__":
    print(minInsertions("zzazz"))  # 0
    print(minInsertions("mbadm"))  # 2
