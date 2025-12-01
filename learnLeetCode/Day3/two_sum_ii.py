"""
Two Sum II — Input array is sorted (Easy)

Approach: Two pointers starting at both ends, moving inward based on sum.
Time: O(n), Space: O(1).
"""
from typing import List


def two_sum(numbers: List[int], target: int) -> List[int]:
    """Return 1-based indices of the two numbers that add up to target.

    Parameters
    ----------
    numbers: List[int]
        Non-decreasing sorted list of integers.
    target: int
        Desired sum.

    Returns
    -------
    List[int]
        [i+1, j+1] such that numbers[i] + numbers[j] == target, or [] if none.
    """
    left, right = 0, len(numbers) - 1
    while left < right:
        s = numbers[left] + numbers[right]
        if s == target:
            return [left + 1, right + 1]
        if s < target:
            left += 1
        else:
            right -= 1
    return []


if __name__ == "__main__":  # simple smoke tests
    assert two_sum([2, 7, 11, 15], 9) == [1, 2]
    assert two_sum([2, 3, 4], 6) == [1, 3]
    assert two_sum([-1, 0], -1) == [1, 2]
    print("two_sum_ii.py: all tests passed")
