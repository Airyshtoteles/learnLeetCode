# LC 52 — N-Queens II
# Backtracking with bitmasks

def totalNQueens(n: int) -> int:
    maskAll = (1 << n) - 1
    ans = 0
    def dfs(row: int, cols: int, diag: int, anti: int):
        nonlocal ans
        if row == n:
            ans += 1
            return
        avail = maskAll & ~(cols | diag | anti)
        while avail:
            p = avail & -avail
            avail -= p
            dfs(row+1, cols | p, ((diag | p) << 1) & maskAll, ((anti | p) >> 1))
    dfs(0, 0, 0, 0)
    return ans

if __name__ == "__main__":
    print(totalNQueens(4))  # 2
