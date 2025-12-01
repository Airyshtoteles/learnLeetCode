# Day 18 — Part 1: Trapping Rain Water II (LC 407)

Solve in Python and C++ using the classic min-heap + BFS from the border approach.

Key idea:
- Push all border cells into a min-heap (priority queue) as the initial "water level".
- Pop the lowest cell and relax its neighbors:
  - If neighbor height < current water level, it traps water: add (level - height).
  - Push neighbor with height = max(current level, neighbor height).
- Use visited to avoid re-processing.

Complexity:
- Time: O(n*m*log(n*m)) due to heap operations.
- Space: O(n*m) for visited and heap.

Files:
- trap_rain_water_ii.py — Python implementation with example.
- trap_rain_water_ii.cpp — C++ implementation with example in main().

How to run (optional):
- Python: run the script directly.
- C++: compile with a C++17 compiler and run the produced binary.
