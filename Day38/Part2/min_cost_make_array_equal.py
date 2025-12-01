from typing import List

def min_cost(nums: List[int], cost: List[int]) -> int:
    A = sorted(zip(nums, cost))
    total_w = sum(cost)
    half = (total_w + 1) // 2
    acc = 0
    median = A[-1][0]
    for v, w in A:
        acc += w
        if acc >= half:
            median = v
            break
    res = 0
    for v, w in A:
        res += w * abs(v - median)
    return res

if __name__ == "__main__":
    print(min_cost([1,3,5,2], [2,3,1,14]))  # Example style
