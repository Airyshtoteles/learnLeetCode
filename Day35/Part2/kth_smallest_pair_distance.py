from typing import List

def count_pairs(nums: List[int], d: int) -> int:
    n = len(nums)
    j = 0
    cnt = 0
    for i in range(n):
        while j < n and nums[j] - nums[i] <= d:
            j += 1
        cnt += max(0, j - i - 1)
    return cnt

def smallest_distance_pair(nums: List[int], k: int) -> int:
    nums.sort()
    lo, hi = 0, nums[-1] - nums[0]
    while lo < hi:
        mid = (lo + hi) // 2
        if count_pairs(nums, mid) >= k:
            hi = mid
        else:
            lo = mid + 1
    return lo

if __name__ == "__main__":
    print(smallest_distance_pair([1,3,1], 1))  # Expected 0
