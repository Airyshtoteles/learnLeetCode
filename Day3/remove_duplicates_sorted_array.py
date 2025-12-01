"""
Remove Duplicates from Sorted Array (Easy)

Approach: Two pointers; overwrite in-place when encountering a new unique value.
Time: O(n), Space: O(1).
"""
from typing import List


def remove_duplicates(nums: List[int]) -> int:
    """Remove duplicates in-place, return length k of unique prefix.

    Modifies nums so that nums[:k] are the unique elements in order.
    """
    if not nums:
        return 0
    write = 1
    for read in range(1, len(nums)):
        if nums[read] != nums[write - 1]:
            nums[write] = nums[read]
            write += 1
    return write


if __name__ == "__main__":  # simple smoke tests
    arr = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
    k = remove_duplicates(arr)
    assert k == 5 and arr[:k] == [0, 1, 2, 3, 4]

    arr2 = []
    k2 = remove_duplicates(arr2)
    assert k2 == 0 and arr2 == []

    arr3 = [1]
    k3 = remove_duplicates(arr3)
    assert k3 == 1 and arr3[:k3] == [1]

    arr4 = [1, 1, 1]
    k4 = remove_duplicates(arr4)
    assert k4 == 1 and arr4[:k4] == [1]

    print("remove_duplicates_sorted_array.py: all tests passed")
