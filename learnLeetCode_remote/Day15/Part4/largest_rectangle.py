from typing import List

# LeetCode 84 — Largest Rectangle in Histogram
# Monotonic stack, append sentinel 0 to flush.

def largestRectangleArea(heights: List[int]) -> int:
    stack = []  # indices of increasing heights
    res = 0
    h = heights + [0]
    for i, ht in enumerate(h):
        while stack and h[stack[-1]] > ht:
            H = h[stack.pop()]
            L = stack[-1] if stack else -1
            width = i - L - 1
            res = max(res, H * width)
        stack.append(i)
    return res

if __name__ == "__main__":
    print(largestRectangleArea([2,1,5,6,2,3]))  # 10
