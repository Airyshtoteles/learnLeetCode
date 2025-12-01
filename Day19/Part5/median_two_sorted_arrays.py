# LC 4 — Median of Two Sorted Arrays
# Binary search partition on the smaller array
from typing import List

def findMedianSortedArrays(nums1: List[int], nums2: List[int]) -> float:
    A, B = nums1, nums2
    if len(A) > len(B):
        A, B = B, A
    m, n = len(A), len(B)
    total = m + n
    half = total // 2
    lo, hi = 0, m
    while True:
        i = (lo + hi) // 2  # A partition size
        j = half - i
        Aleft = A[i-1] if i > 0 else float('-inf')
        Aright = A[i] if i < m else float('inf')
        Bleft = B[j-1] if j > 0 else float('-inf')
        Bright = B[j] if j < n else float('inf')
        if Aleft <= Bright and Bleft <= Aright:
            if total % 2:
                return float(min(Aright, Bright))
            return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0
        elif Aleft > Bright:
            hi = i - 1
        else:
            lo = i + 1

if __name__ == "__main__":
    print(findMedianSortedArrays([1,3],[2]))  # 2.0
