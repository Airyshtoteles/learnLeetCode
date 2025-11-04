import math

def winnerSquareGame(n: int) -> bool:
    dp = [False] * (n + 1)
    for i in range(1, n + 1):
        k = 1
        win = False
        while k * k <= i:
            if not dp[i - k * k]:
                win = True
                break
            k += 1
        dp[i] = win
    return dp[n]

if __name__ == "__main__":
    for n in [1, 2, 3, 4, 7, 17]:
        print(n, "->", winnerSquareGame(n))
