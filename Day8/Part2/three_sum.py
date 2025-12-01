"""
Day 8 — Part 2: 3Sum

Find all unique triplets that sum to zero.
Approach: Sort + O(n^2) two-pointers, skip duplicates for i, left, and right.
Time: O(n^2), Space: O(1) extra (excluding output).
"""
from typing import List


def three_sum(nums: List[int]) -> List[List[int]]:
    nums.sort()
    n = len(nums)
    res: List[List[int]] = []

    for i in range(n):
        if i > 0 and nums[i] == nums[i - 1]:
            continue  # skip duplicate anchor
        if nums[i] > 0:
            break     # no further triplets possible

        l, r = i + 1, n - 1
        while l < r:
            s = nums[i] + nums[l] + nums[r]
            if s == 0:
                res.append([nums[i], nums[l], nums[r]])
                # move left and right to next different values
                l += 1
                while l < r and nums[l] == nums[l - 1]:
                    l += 1
                r -= 1
                while l < r and nums[r] == nums[r + 1]:
                    r -= 1
            elif s < 0:
                l += 1
            else:
                r -= 1
    return res


if __name__ == "__main__":
    assert three_sum([-1,0,1,2,-1,-4]) in (
        [[-1,-1,2],[-1,0,1]],
        [[-1,0,1],[-1,-1,2]],
    )
    assert three_sum([]) == []
    assert three_sum([0]) == []
    assert three_sum([0,0,0]) == [[0,0,0]]
    print("Day8 Part2 three_sum.py: all tests passed")