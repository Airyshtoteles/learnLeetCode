"""
Day 8 — Part 3: 4Sum

Find all unique quadruplets [a,b,c,d] such that a + b + c + d == target.
Approach: Sort; fix two indices (i, j), then two-pointers for the inner pair.
Skip duplicates for i, j, left, and right to avoid repeated quadruplets.
Time: O(n^3), Space: O(1) extra (excluding output).
"""
from typing import List


def four_sum(nums: List[int], target: int) -> List[List[int]]:
    nums.sort()
    n = len(nums)
    res: List[List[int]] = []
    for i in range(n):
        if i > 0 and nums[i] == nums[i - 1]:
            continue
        # pruning (optional): if smallest possible sum > target or largest < target, can break/continue
        for j in range(i + 1, n):
            if j > i + 1 and nums[j] == nums[j - 1]:
                continue
            l, r = j + 1, n - 1
            while l < r:
                s = nums[i] + nums[j] + nums[l] + nums[r]
                if s == target:
                    res.append([nums[i], nums[j], nums[l], nums[r]])
                    l += 1
                    while l < r and nums[l] == nums[l - 1]:
                        l += 1
                    r -= 1
                    while l < r and nums[r] == nums[r + 1]:
                        r -= 1
                elif s < target:
                    l += 1
                else:
                    r -= 1
    return res


if __name__ == "__main__":
    # Classic example
    arr = [1,0,-1,0,-2,2]
    out = four_sum(arr, 0)
    # Expected (order may vary):
    # [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
    assert sorted(out) == sorted([[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]])

    assert four_sum([], 0) == []
    assert four_sum([0,0,0,0], 0) == [[0,0,0,0]]
    print("Day8 Part3 four_sum.py: all tests passed")
