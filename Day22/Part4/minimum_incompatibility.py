# LC 1681 — Minimum Incompatibility
# DP over bitmask selecting valid groups of size n//k
from typing import List
from math import inf
from collections import Counter


def minimumIncompatibility(nums: List[int], k: int) -> int:
    n = len(nums)
    group = n // k

    # Early pruning: any value appears more than k times -> impossible
    freq = Counter(nums)
    if any(c > k for c in freq.values()):
        return -1

    # Precompute valid subsets of indices of size 'group' with all unique values
    # and their incompatibility (max - min)
    idx = list(range(n))
    valid_cost = {}

    # Enumerate all subsets of size 'group'
    # n <= 16 -> choose(n, group) manageable
    from itertools import combinations
    for comb in combinations(idx, group):
        vals = [nums[i] for i in comb]
        if len(set(vals)) != group:
            continue
        cost = max(vals) - min(vals)
        # Turn to bitmask
        m = 0
        for i in comb:
            m |= 1 << i
        valid_cost[m] = cost

    # DP over masks; only pick subsets that include the first free index
    msz = 1 << n
    dp = [inf] * msz
    dp[0] = 0

    for mask in range(msz):
        if dp[mask] == inf:
            continue
        if mask == msz - 1:
            continue
        # find first free index
        i = 0
        while (mask >> i) & 1:
            i += 1
        rem = ((1 << n) - 1) ^ mask
        # iterate valid subsets that include i and are subset of rem
        sub = rem
        while sub:
            if (sub & (1 << i)) and (sub in valid_cost):
                # ensure subset size is exactly 'group'
                if sub.bit_count() == group:
                    dp[mask | sub] = min(dp[mask | sub], dp[mask] + valid_cost[sub])
            sub = (sub - 1) & rem

    ans = dp[msz - 1]
    return -1 if ans == inf else ans


if __name__ == "__main__":
    print(minimumIncompatibility([1,2,1,4], 2))  # 4, groups: [1,2],[1,4] -> 1 + 3 = 4
    print(minimumIncompatibility([6,3,8,1,3,1,2,2], 4))  # 6
