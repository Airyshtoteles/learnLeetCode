from typing import List

# LC 2547 — Minimum Cost to Split Array
# Cost of subarray = k + number_of_duplicate_elements_in_subarray
# Duplicates counting rule: for an element with frequency f
#   contributes f if f >= 2 else 0
# Incremental: when a frequency hits 2 -> +2; when >2 -> +1
# DP: dp[i] = min cost to split nums[:i]
#   dp[0] = 0
#   dp[i] = min_{j<i} dp[j] + k + duplicates(nums[j:i])
# Note: This O(n^2) reference solution is straightforward and clear.

class Solution:
    def minCost(self, nums: List[int], k: int) -> int:
        n = len(nums)
        dp = [10**18] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            freq = {}
            dup = 0
            # build backwards segment [j, i)
            for j in range(i - 1, -1, -1):
                x = nums[j]
                f = freq.get(x, 0) + 1
                freq[x] = f
                if f == 2:
                    dup += 2
                elif f > 2:
                    dup += 1
                dp[i] = min(dp[i], dp[j] + k + dup)
        return dp[n]

if __name__ == "__main__":
    print(Solution().minCost([1,2,1,2,1,3,3], 2))  # Expected 8
