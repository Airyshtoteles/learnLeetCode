from functools import lru_cache

# LeetCode 1553 — Minimum Number of Days to Eat N Oranges
# f(n) = 1 + min(n%2 + f(n//2), n%3 + f(n//3))
# Intuition: Spend n%2 days to make n divisible by 2 (eat 1/day), then 1 day to eat n/2.
# Similarly for 3: spend n%3 days then 1 day to eat 2n/3, i.e., recurse with n//3.

class Solution:
    @lru_cache(maxsize=None)
    def minDays(self, n: int) -> int:
        if n <= 1:
            return n
        # eat to divisible by 2 or by 3, plus one day for the bulk operation
        by2 = n % 2 + self.minDays(n // 2)
        by3 = n % 3 + self.minDays(n // 3)
        return 1 + min(by2, by3)

if __name__ == "__main__":
    print(Solution().minDays(10))  # Expected 4