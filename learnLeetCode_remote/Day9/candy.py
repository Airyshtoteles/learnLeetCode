"""
LeetCode 135 — Candy
Day 9

Greedy two-pass:
- Everyone starts with 1 candy.
- Left->right: if ratings[i] > ratings[i-1], candies[i] = candies[i-1] + 1
- Right->left: if ratings[i] > ratings[i+1], candies[i] = max(candies[i], candies[i+1] + 1)
Return sum(candies).

Time: O(n), Space: O(n)
"""
from typing import List


def candy(ratings: List[int]) -> int:
    n = len(ratings)
    if n == 0:
        return 0
    candies = [1] * n
    # Left to right
    for i in range(1, n):
        if ratings[i] > ratings[i - 1]:
            candies[i] = candies[i - 1] + 1
    # Right to left
    for i in range(n - 2, -1, -1):
        if ratings[i] > ratings[i + 1]:
            candies[i] = max(candies[i], candies[i + 1] + 1)
    return sum(candies)


if __name__ == "__main__":
    assert candy([1,0,2]) == 5
    assert candy([1,2,2]) == 4
    assert candy([1,1,1]) == 3
    assert candy([1,2,3,4,5]) == 15
    assert candy([5,4,3,2,1]) == 15
    assert candy([]) == 0
    print("Day9 candy.py: all tests passed")
