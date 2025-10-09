"""
Move Zeroes (Easy)

Approach: Two-pointer compaction of non-zeros then fill trailing zeros.
Time: O(n), Space: O(1), minimal writes.
"""
from typing import List


def move_zeroes(nums: List[int]) -> None:
    """Move all zeros to the end in-place while preserving relative order.

    Do not return anything; modify nums in-place.
    """
    write = 0
    for read in range(len(nums)):
        if nums[read] != 0:
            nums[write] = nums[read]
            write += 1
    for i in range(write, len(nums)):
        nums[i] = 0


if __name__ == "__main__":  # simple smoke tests
    arr = [0, 1, 0, 3, 12]
    move_zeroes(arr)
    assert arr == [1, 3, 12, 0, 0]

    arr2 = [0]
    move_zeroes(arr2)
    assert arr2 == [0]

    arr3 = [1, 2, 3]
    move_zeroes(arr3)
    assert arr3 == [1, 2, 3]

    arr4 = [0, 0, 0]
    move_zeroes(arr4)
    assert arr4 == [0, 0, 0]

    arr5 = [4, 0, 5, 0, 0, -1]
    move_zeroes(arr5)
    assert arr5 == [4, 5, -1, 0, 0, 0]

    print("move_zeroes.py: all tests passed")
