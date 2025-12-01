# Day 19 — Part 1: Trapping Rain Water II (LC 407)

Approach (min-heap + BFS from border):
- Push all border cells with their heights into a min-heap.
- Pop the lowest, try to relax neighbors: if neighbor is lower, collect water (diff) and push neighbor with water level = max(current level, neighbor height).
- Mark visited to avoid reprocessing.

Complexity:
- Time: O(m*n*log(m*n))
- Space: O(m*n)

Files:
- trap_rain_water_ii.py — Python implementation with example.
- trap_rain_water_ii.cpp — C++ implementation with example in main().
