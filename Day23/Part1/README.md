# Day 23 — Part 1: The Mirror of Time

Goal: Given an array, find the minimum total cost to rearrange it into a palindrome where a swap of indices (i, j) costs |i − j|. If impossible, return -1.

Approach (two-pointer greedy):
- Use the classic greedy for minimum adjacent swaps to make palindrome, but treat a single swap (k, j) as cost (j − k).
- Maintain i, j pointers.
  - If a[i] == a[j], move inward.
  - Else find k from the right where a[k] == a[i]. If found, swap a[k] with a[j] with cost (j − k); move inward.
  - If not found (a[i] is the odd singleton), bubble it one step right (swap i and i+1) with cost 1; repeat.
- After processing, validate palindrome; if not, answer is -1.

Notes:
- Palindrome feasibility requires at most one value with odd count. If all elements are unique and n > 1, it’s impossible; this method returns -1.
- The provided example with all-unique values suggests a typo; under the standard definition it would be impossible. Use an input with pairs to get a finite cost.

Complexity: O(n^2) worst-case (due to inner search), O(n) extra space.

Files:
- mirror_of_time.py — Python implementation with a few demos.
- mirror_of_time.cpp — C++17 implementation with small main() tests.
