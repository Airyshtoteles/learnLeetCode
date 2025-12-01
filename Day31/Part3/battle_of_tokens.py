from typing import List

def max_score_diff(nums: List[int]) -> int:
    n = len(nums)
    if n == 0:
        return 0
    dp = [[0]*n for _ in range(n)]
    for i in range(n):
        dp[i][i] = nums[i]
    for i in range(n-1):
        dp[i][i+1] = max(nums[i] - nums[i+1], nums[i+1] - nums[i], nums[i] + nums[i+1])
        # Taking 2 from a side when two remain just gets both
    for length in range(3, n+1):
        for l in range(0, n - length + 1):
            r = l + length - 1
            best = float('-inf')
            # 1 from left
            best = max(best, nums[l] - dp[l+1][r])
            # 2 from left
            best = max(best, nums[l] + nums[l+1] - (dp[l+2][r] if l+2 <= r else 0))
            # 1 from right
            best = max(best, nums[r] - dp[l][r-1])
            # 2 from right
            best = max(best, nums[r] + nums[r-1] - (dp[l][r-2] if l <= r-2 else 0))
            dp[l][r] = best
    return dp[0][n-1]

if __name__ == "__main__":
    print(max_score_diff([1,5,233,7]))  # Expected 222
