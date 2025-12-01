# Trapping Rain Water II (LeetCode 407)

Difficulty: Hard

Given an m x n height map (grid of non-negative integers), compute how much water it can trap after raining.

## Approach (Border Min-Heap BFS)
- Push all border cells into a min-heap and mark visited.
- Pop the lowest cell `h`. For each neighbor not visited, trapped water is `max(0, h - height[nr][nc])`.
- The neighbor's effective boundary is `max(h, height[nr][nc])`; push it into the heap and continue.

This is equivalent to expanding the lowest boundary inward.

- Time: `O(mn log mn)`
- Space: `O(mn)`
