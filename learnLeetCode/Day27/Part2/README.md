# Dungeon of Equal Souls

Given a tree with n rooms (nodes) and edges, each room i has power[i]. Split the tree into two connected groups (each must be a subtree) by removing exactly one edge, so that the absolute difference between the sums is minimized. Return the minimum difference.

## Approach
- Compute total sum S
- Root the tree arbitrarily (e.g., at 1) and run DFS to compute `sub[i]` = sum of powers in i's subtree
- For each edge (parent, child), if we cut it, the two components have sums `sub[child]` and `S - sub[child]`. Track `min |S - 2*sub[child]|`.

Time: O(n)

## Files
- `equal_souls.py` — Python implementation with example
- `equal_souls.cpp` — C++17 implementation
