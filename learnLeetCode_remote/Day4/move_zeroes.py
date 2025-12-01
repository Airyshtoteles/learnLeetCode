"""
Day 4 — Move Zeroes to End (Optimized)

Problem: Move all zeros to the end of the array while maintaining the order of non-zero elements.
Constraints: In-place, O(n) time, O(1) extra space.

Approach: Single-pass two-pointer with conditional swap to minimize writes.
"""
from typing import List


def move_zeroes(nums: List[int]) -> None:
    write = 0
    for read in range(len(nums)):
        if nums[read] != 0:
            if read != write:
                nums[write], nums[read] = nums[read], nums[write]
            write += 1


if __name__ == "__main__":
    arr = [0, 1, 0, 3, 12]
    move_zeroes(arr)
    assert arr == [1, 3, 12, 0, 0]

    arr2 = [0, 0, 1]
    move_zeroes(arr2)
    assert arr2 == [1, 0, 0]

    arr3 = [1, 2, 3]
    move_zeroes(arr3)
    assert arr3 == [1, 2, 3]

    arr4 = [0]
    move_zeroes(arr4)
    assert arr4 == [0]

    print("Day4 move_zeroes.py: all tests passed")
