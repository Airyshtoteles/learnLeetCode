from functools import lru_cache
from typing import List

# LC 1547 — Minimum Cost to Cut a Stick (Interval DP)

class Solution:
    def minCost(self, n: int, cuts: List[int]) -> int:
        cuts = sorted(cuts + [0, n])
        m = len(cuts)

        @lru_cache(None)
        def dp(l: int, r: int) -> int:
            # min cost to cut between cuts[l] and cuts[r], exclusive
            if l + 1 >= r:
                return 0
            best = float('inf')
            for i in range(l + 1, r):
                cost = cuts[r] - cuts[l] + dp(l, i) + dp(i, r)
                if cost < best:
                    best = cost
            return best

        return dp(0, m - 1)

if __name__ == "__main__":
    print(Solution().minCost(7, [1,3,4,5]))  # Expected 16
