"""
Day 8 — Minimum Number of Taps to Open to Water a Garden (#1326)

Greedy (Jump Game II style):
- Build max reach starting from each position using ranges
- Sweep from left to right, expanding current coverage; when reaching the end
  of current coverage, open a new tap (increment) and extend to farthest reach

Time: O(n), Space: O(n)
"""
from typing import List


def min_taps(n: int, ranges: List[int]) -> int:
    if n == 0:
        return 0
    # maxReach[i] = farthest right we can reach starting watering at position i
    max_reach = [0] * (n + 1)
    for i, r in enumerate(ranges):
        left = max(0, i - r)
        right = min(n, i + r)
        max_reach[left] = max(max_reach[left], right)

    taps = 0
    curr_end = 0
    farthest = 0
    for i in range(n):  # we need to cover up to position n
        farthest = max(farthest, max_reach[i])
        if i == curr_end:
            if farthest == curr_end:
                return -1  # cannot extend coverage
            taps += 1
            curr_end = farthest
            if curr_end >= n:
                break
    return taps if curr_end >= n else -1


if __name__ == "__main__":
    # Example
    assert min_taps(5, [3,4,1,1,0,0]) == 1

    # Basic checks
    assert min_taps(0, [0]) == 0
    assert min_taps(3, [0,0,0,0]) == -1
    assert min_taps(3, [3,0,0,0]) == 1
    assert min_taps(7, [1,2,1,0,2,1,0,1]) == 3  # known case

    print("Day8 min_taps.py: all tests passed")