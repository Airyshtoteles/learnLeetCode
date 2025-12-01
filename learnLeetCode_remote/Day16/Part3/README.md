# Day 16 — Part 3: Number of Increasing Paths in a Grid (LC 2328)

We do DFS with memoization:
- Each cell contributes 1 (itself) plus paths to strictly greater neighbors.
- Modulo 1e9+7 for the total.

Files:
- `increasing_paths.py`
- `increasing_paths.cpp`

Try:
```
python increasing_paths.py
```
