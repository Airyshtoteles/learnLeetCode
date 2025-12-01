# Day 18 — Part 2: Merge k Sorted Lists (LC 23)

Min-heap approach:
- Push the head of each non-empty list to a priority queue keyed by node value.
- Repeatedly extract the smallest node, append to the result list, and push its next.

Complexity:
- Time: O(N log k), where N is total nodes and k is number of lists.
- Space: O(k) for the heap.

Files:
- merge_k_sorted_lists.py — Python implementation with example.
- merge_k_sorted_lists.cpp — C++ implementation with example in main().
