"""
Tower Game: Destruction Order

Given n towers with heights. One shot destroys the chosen tower and also its immediate
neighbors that are strictly smaller than it. Find the minimum number of shots to destroy all.

Input:
- First line: n
- Second line: n integers for heights

Output:
- Single integer: minimal number of shots

Approach:
- Sort indices by height descending.
- Keep a removed[] array. Iterate in that order; when you pick an index not yet removed,
  increment shots, remove it, and remove strictly smaller immediate neighbors if present.
- O(n log n).
"""
from typing import List


def min_shots(heights: List[int]) -> int:
    n = len(heights)
    if n == 0:
        return 0
    removed = [False] * n
    order = sorted(range(n), key=lambda i: heights[i], reverse=True)
    shots = 0
    for i in order:
        if removed[i]:
            continue
        shots += 1
        removed[i] = True
        # Left neighbor
        if i - 1 >= 0 and (not removed[i - 1]) and heights[i - 1] < heights[i]:
            removed[i - 1] = True
        # Right neighbor
        if i + 1 < n and (not removed[i + 1]) and heights[i + 1] < heights[i]:
            removed[i + 1] = True
    return shots


def _read_ints() -> List[int]:
    import sys
    return list(map(int, sys.stdin.readline().strip().split()))


def main():
    import sys
    data = sys.stdin.read().strip().split()
    if not data:
        demo = [3, 1, 4, 1, 5]
        print(min_shots(demo))
        return
    it = iter(data)
    n = int(next(it))
    arr = [int(next(it)) for _ in range(n)]
    print(min_shots(arr))


if __name__ == "__main__":
    main()
