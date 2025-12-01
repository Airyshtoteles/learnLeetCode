# Day 31 — Part 6: Shifted Grid Collapse

We have an N x N grid of integers. A move picks a column, shifts all numbers in that column downward (gravity). After shifting, any 3+ same numbers consecutively in that column explode (become 0). Explosions may cause falling, so repeat collapse in that column until stable. Up to k moves. Return the maximum total number of numbers destroyed (counted as elements that were part of any explosion).

Approach:
- DFS + memo over (grid_state_serialized, moves_left). For each column, simulate one move:
  1) Gravity: compress non-zero numbers downward (zeros on top).
  2) Find runs of length >= 3 of identical values; mark them as destroyed (count how many new cells destroyed this round), set them to 0.
  3) If anything destroyed, repeat gravity and explosion detection until no more explosions in that column (chain reactions allowed).
- Recurse with moves_left - 1 and take max destroyed.

Complexity: Exponential in k times N branching, but N,k small (e.g., N<=6, k<=6) should be fine with memoization.

Files:
- shifted_grid_collapse.py — Python implementation.
- shifted_grid_collapse.cpp — C++17 implementation.
