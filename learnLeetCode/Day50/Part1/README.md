# Day 50 Part 1: Time-Reversal Dungeon

## Problem Description
You are in a dungeon with `n` rooms. Each room `i` has a monster with power `monster[i]`.
You can perform at most `k` **Time Reversals**: reverse a segment `[l, r]` of the monster array.
Your goal is to minimize the total damage:
`damage = sum((i + 1) * monster[i] for i in range(n))`

## Approach
The cost function is a dot product of indices `[1, 2, ..., n]` and the monster array.
To minimize this sum, we ideally want the largest monster values to be at the smallest indices (sorted descending).
Since `k` is small (50) but `n` is large (200,000), we cannot explore the full state space.
We use a **Greedy with Lookahead** or **Iterative Improvement** approach.
In each step (up to `k`), we look for a reversal that gives the maximum reduction in damage.
However, finding the *best* reversal takes `O(N^2)`, which is too slow.
We can optimize by focusing on "out of place" elements.
Specifically, we want to move large elements to the left.
We can identify the largest element that is "too far right" and the smallest element "too far left" and try to swap/reverse them.

Given the constraints and the "Hard" nature, this might be a heuristic challenge.
We will implement a **Simulated Annealing** or **Randomized Greedy** approach to find a good solution within the time limit, or a simplified greedy if a clear structure exists.
For this implementation, we'll use a **Greedy Strategy**:
1. Identify the pair `(i, j)` with `i < j` such that `monster[i] < monster[j]` which contributes most to the cost (i.e., swapping them would reduce cost significantly).
2. Reverse the segment `[i, j]`.
3. Repeat `k` times.

## Complexity
- **Time:** `O(K * N)` (approximate, depending on candidate selection).
- **Space:** `O(N)`.
