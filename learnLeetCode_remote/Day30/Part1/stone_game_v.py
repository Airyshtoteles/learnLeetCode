from functools import lru_cache
from typing import List


def stoneGameV(stoneValue: List[int]) -> int:
    n = len(stoneValue)
    prefix = [0] * (n + 1)
    for i in range(n):
        prefix[i + 1] = prefix[i] + stoneValue[i]

    def range_sum(l: int, r: int) -> int:
        return prefix[r + 1] - prefix[l]

    @lru_cache(maxsize=None)
    def dp(l: int, r: int) -> int:
        if l >= r:
            return 0
        best = 0
        # try all splits
        for k in range(l, r):
            left = range_sum(l, k)
            right = range_sum(k + 1, r)
            if left < right:
                best = max(best, left + dp(l, k))
            elif left > right:
                best = max(best, right + dp(k + 1, r))
            else:
                # equal sums: can choose either side
                best = max(best, left + max(dp(l, k), dp(k + 1, r)))
        return best

    return dp(0, n - 1)


if __name__ == "__main__":
    # Quick sanity checks
    tests = [
        [6, 2, 3, 4, 5, 5],
        [7, 7, 7, 7, 7, 7, 7],
        [4],
        [1, 2],
        [3, 8, 4, 5, 2],
    ]
    for arr in tests:
        print(arr, "->", stoneGameV(arr))
