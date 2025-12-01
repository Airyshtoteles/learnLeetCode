from typing import List

def min_swaps_circular(nums: List[int], k: int) -> int:
    n = len(nums)
    pos = [i for i, v in enumerate(nums) if v == 1]
    m = len(pos)
    if k == 0 or k == 1:
        return 0
    if m < k:
        return -1
    pos2 = pos + [x + n for x in pos]
    # adjusted positions remove index shift impact
    adj = [pos2[i] - i for i in range(len(pos2))]
    pref = [0]
    for v in adj:
        pref.append(pref[-1] + v)
    ans = 10**18
    for s in range(m):
        e = s + k - 1
        mid = (s + e) // 2
        med = adj[mid]
        # left part [s..mid], right part [mid..e]
        left_sum = med * (mid - s) - (pref[mid] - pref[s])
        right_sum = (pref[e+1] - pref[mid+1]) - med * (e - mid)
        cost = left_sum + right_sum
        # For even k, subtract the internal alignment offset: (k//2)*(k - k//2)
        if k % 2 == 0:
            cost -= (k // 2) * (k - k // 2)
        ans = min(ans, cost)
    return int(ans)

if __name__ == "__main__":
    print(min_swaps_circular([1,0,1,0,1], 2))  # Expected 0
