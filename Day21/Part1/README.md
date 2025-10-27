# Day 21 — Part 1: Number of Ways to Reorder Array to Get Same BST (LC 1569)

Idea:
- The relative order among left subtree elements and among right subtree elements must be preserved, but interleavings between left and right can be any that keeps order within each side.
- So ways(arr) = C(L+R, L) * ways(left) * ways(right).
- Answer required by problem is ways(nums) - 1 (exclude the original order).

Complexity:
- Precompute combinations up to n via Pascal O(n^2).
- Solve recursing across subtrees.

Files:
- same_bst_reorders.py — Python solution with example.
- same_bst_reorders.cpp — C++ solution with example in main().
