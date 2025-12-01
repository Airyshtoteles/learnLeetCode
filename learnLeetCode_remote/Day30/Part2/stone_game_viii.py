from functools import lru_cache
from itertools import accumulate
from typing import List


def stoneGameVIII(stones: List[int]) -> int:
    s = list(accumulate(stones))
    n = len(stones)

    @lru_cache(maxsize=None)
    def dfs(i: int) -> int:
        # When i is at or beyond the last index, only option is to take all remaining
        if i >= n - 1:
            return s[-1]
        # Either skip taking at i (pass to i+1) or take prefix up to i now
        skip = dfs(i + 1)
        take = s[i] - dfs(i + 1)
        return max(skip, take)

    # Must take at least 2 stones initially -> start from i = 1
    return dfs(1)


if __name__ == "__main__":
    cases = [
        [3, 7, 2, 3],
        [7, -6, 5, 10, 5, -2, -6],
        [-10, -12],
        [1, 2],
    ]
    for arr in cases:
        print(arr, "->", stoneGameVIII(arr))
