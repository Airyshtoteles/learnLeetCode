# LC 2009 — Minimum Number of Operations to Make Array Continuous
# Sort unique + sliding window to keep most that already fit into a window of size n (values within [x, x+n-1])
from typing import List

def minOperations(nums: List[int]) -> int:
    n = len(nums)
    a = sorted(set(nums))
    m = len(a)
    ans_keep = 0
    j = 0
    for i in range(m):
        while j < m and a[j] < a[i] + n:
            j += 1
        ans_keep = max(ans_keep, j - i)
    return n - ans_keep

if __name__ == "__main__":
    print(minOperations([4,2,5,3]))  # 0
    print(minOperations([1,2,3,5,6]))  # 1
