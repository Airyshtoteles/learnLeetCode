# Day 19 — Part 3: Paint House III (LC 1473)

Approach:
- DP over (index i, color j, neighborhoods k): dp[i][j][k] = min cost to paint up to i with house i colored j and exactly k neighborhoods.
- Transition from previous color pc: if j == pc then k unchanged; else k+1.
- Handle pre-colored houses by restricting allowed color and zero extra cost.

Complexity:
- Time: O(m * n * n * target) in worst case.
- Space: O(n * target) using rolling arrays.

Files:
- paint_house_iii.py — Python DP with rolling arrays; includes example.
- paint_house_iii.cpp — C++ counterpart with example in main().
