from typing import List

def min_subarray(nums: List[int], p: int) -> int:
    total = sum(nums)
    target = total % p
    if target == 0:
        return 0
    seen = {0: -1}
    res = len(nums)
    cur = 0
    for i, x in enumerate(nums):
        cur = (cur + x) % p
        need = (cur - target) % p
        if need in seen:
            res = min(res, i - seen[need])
        seen[cur] = i
    return res if res < len(nums) else -1

if __name__ == "__main__":
    print(min_subarray([3,1,4,2], 6))  # Expected 1 (remove [4])
