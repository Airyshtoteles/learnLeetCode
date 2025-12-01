"""
Container With Most Water (Medium) — Bonus

Approach: Two pointers from both ends; move the shorter side inward.
Time: O(n), Space: O(1).
"""
from typing import List


def max_area(height: List[int]) -> int:
    left, right = 0, len(height) - 1
    best = 0
    while left < right:
        h = min(height[left], height[right])
        area = h * (right - left)
        if area > best:
            best = area
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1
    return best


if __name__ == "__main__":
    assert max_area([1,8,6,2,5,4,8,3,7]) == 49
    assert max_area([1,1]) == 1
    assert max_area([1,2,1]) == 2
    print("container_with_most_water.py: all tests passed")
