# LC 1745 — Palindrome Partitioning IV
# Check if s can be split into 3 palindromic substrings

def checkPartitioning(s: str) -> bool:
    n = len(s)
    pal = [[False]*n for _ in range(n)]
    for i in range(n-1, -1, -1):
        for j in range(i, n):
            if s[i] == s[j] and (j - i <= 1 or pal[i+1][j-1]):
                pal[i][j] = True
    # Try splits: [0..i], [i+1..j], [j+1..n-1]
    for i in range(n-2):
        if not pal[0][i]:
            continue
        for j in range(i+1, n-1):
            if pal[i+1][j] and pal[j+1][n-1]:
                return True
    return False

if __name__ == "__main__":
    print(checkPartitioning("abcbdd"))  # True
