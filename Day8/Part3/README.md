# Day 8 — Part 3: 4Sum

Problem: Given an integer array `nums` and an integer `target`, return all unique quadruplets `[a,b,c,d]` such that `a + b + c + d == target`. The solution set must not contain duplicate quadruplets.

Approach
- Sort the array.
- Fix two indices `i` and `j` (outer two loops), then run two-pointers `l` and `r` on the remaining range.
- Skip duplicates for `i`, `j`, `l`, and `r` to avoid repeated quadruplets.
- Time complexity: O(n^3). Space complexity: O(1) extra (excluding output).

Files
- four_sum.py — Python implementation with small assertions.
- four_sum.cpp — C++17 implementation with a simple demo and sanity checks.

How to run
- Python (from this folder):
  - Run `python four_sum.py`
- C++ (PowerShell):
  - `g++ -std=c++17 four_sum.cpp -O2 -o four_sum.exe ; if ($?) { .\four_sum.exe }`

Notes
- Uses long long when summing four integers to avoid overflow while comparing to target.
- Results are returned in sorted non-decreasing order per quadruplet; overall order of quadruplets is not specified.
