from typing import List


def min_changes_to_make_pal(s: str) -> int:
    i, j = 0, len(s) - 1
    changes = 0
    while i < j:
        if s[i] != s[j]:
            changes += 1
        i += 1
        j -= 1
    return changes


def min_changes_split_k_palindromes(s: str, K: int) -> int:
    n = len(s)
    # Precompute cost[i][j]: changes to make s[i..j] palindrome
    cost = [[0]*n for _ in range(n)]
    for length in range(2, n+1):
        for i in range(0, n - length + 1):
            j = i + length - 1
            inner = cost[i+1][j-1] if i + 1 <= j - 1 else 0
            cost[i][j] = inner + (0 if s[i] == s[j] else 1)
    INF = 10**9
    dp = [[INF]*(n+1) for _ in range(K+1)]
    dp[0][0] = 0
    for k in range(1, K+1):
        for i in range(1, n+1):
            best = INF
            # try last cut at t (substring t..i-1)
            for t in range(k-1, i):  # at least k-1 chars to place k-1 parts
                c = 0 if t == i-1 else cost[t][i-1]
                if dp[k-1][t] + c < best:
                    best = dp[k-1][t] + c
            dp[k][i] = best
    return dp[K][n]


if __name__ == "__main__":
    # Basic sanity checks
    print(min_changes_split_k_palindromes("abc", 2))  # split as "a"|"bc" -> 1
    print(min_changes_split_k_palindromes("aabbc", 3))  # e.g., "aa"|"bb"|"c" -> 0
