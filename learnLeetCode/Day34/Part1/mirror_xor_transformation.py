from typing import List

def min_operations(nums: List[int]) -> int:
    n = len(nums)
    # 0: already all equal
    if all(x == nums[0] for x in nums):
        return 0
    # 1: palindrome
    if all(nums[i] == nums[n-1-i] for i in range(n)):
        return 1
    # else 2
    return 2

if __name__ == "__main__":
    print(min_operations([1,3,2,3,1]))  # 1
    print(min_operations([5,5,5]))      # 0
    print(min_operations([1,2,3]))      # 2
