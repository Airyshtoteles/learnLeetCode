from typing import List

# LC 2218 — Maximum Value of K Coins From Piles
# 1D DP over total coins taken so far, process piles one by one.
# For each pile, precompute prefix sums; update dp[j] from j down to 1.

def maxValueOfCoins(piles: List[List[int]], k: int) -> int:
    dp = [0] * (k + 1)
    for pile in piles:
        # prefix sums, pref[0]=0
        pref = [0]
        running = 0
        for coin in pile:
            running += coin
            pref.append(running)
        m = min(len(pile), k)
        # update dp in descending j to avoid reuse within same pile
        new_dp = dp[:]
        for j in range(1, k + 1):
            best = dp[j]
            limit = min(m, j)
            for x in range(1, limit + 1):
                best = max(best, dp[j - x] + pref[x])
            new_dp[j] = best
        dp = new_dp
    return dp[k]

if __name__ == "__main__":
    print(maxValueOfCoins([[1,100,3],[7,8,9]], 2))  # 101
