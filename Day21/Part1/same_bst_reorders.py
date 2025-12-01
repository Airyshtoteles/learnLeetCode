# LC 1569 — Number of Ways to Reorder Array to Get Same BST
# Combinatorics + recursion: ways = C(n-1, L) * ways(left) * ways(right). Answer is ways - 1.
from typing import List

MOD = 10**9 + 7

class Solution:
    def numOfWays(self, nums: List[int]) -> int:
        n = len(nums)
        # precompute combinations via Pascal
        comb = [[0]*(n+1) for _ in range(n+1)]
        for i in range(n+1):
            comb[i][0] = comb[i][i] = 1
            for j in range(1, i):
                comb[i][j] = (comb[i-1][j-1] + comb[i-1][j]) % MOD

        def solve(arr: List[int]) -> int:
            if len(arr) <= 2:
                return 1
            root = arr[0]
            left = [x for x in arr[1:] if x < root]
            right = [x for x in arr[1:] if x > root]
            L = len(left); R = len(right)
            leftWays = solve(left)
            rightWays = solve(right)
            return comb[L+R][L] * leftWays % MOD * rightWays % MOD

        return (solve(nums) - 1) % MOD

if __name__ == "__main__":
    print(Solution().numOfWays([2,1,3]))  # 1
