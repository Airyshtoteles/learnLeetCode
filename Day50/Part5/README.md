# Day 50 Part 5: Quantum Tile Collapse

## Problem Description
You have an `n x n` grid with digits 0-9.
Operation: Pick a tile `(r, c)`, double its value `x -> 2x % 10`.
Effect: "Quantum Collapse" - If 3+ identical adjacent tiles form a cluster, they become 0.
Goal: Make a tile `(r, c)` have value `K` in `<= M` steps.
Return min steps.

## Approach
Since `N <= 20`, the grid is small.
However, the state space is huge.
But we only need to make *one* tile `(r, c)` have value `K`.
We can pick any tile `(i, j)` and double it until it becomes `K`.
We need to check if this process triggers a collapse that destroys our target tile (turns it to 0).
Actually, the problem says "Target: buat sel (r,c) memiliki nilai exact = K".
Wait, "buat sel (r,c)". Is `(r,c)` fixed?
"Input: grid, r, c, K, M". Yes, target coordinates are fixed.
So we need `grid[r][c]` to become `K`.
We can operate on `grid[r][c]` directly.
Or we can operate on neighbors to clear space?
But operating on neighbors doesn't change `grid[r][c]`'s value (unless it collapses).
So we MUST operate on `grid[r][c]` to change its value.
Unless `grid[r][c]` is already `K`.
If `grid[r][c]` is not `K`, we must double it.
Doubling `v` -> `2v % 10`.
This forms a cycle.
We check if `K` is reachable from `grid[r][c]` in `<= M` steps.
If reachable, let `s` be the steps.
We simulate the process:
For `step` 1 to `s`:
  - Double `grid[r][c]`.
  - Check for collapse.
  - If `grid[r][c]` becomes 0 (collapsed), and `K != 0`, we fail this path.
  - If `grid[r][c]` becomes `K` and we are done, success.
  - Note: Collapse happens *after* doubling.
  - If `grid[r][c]` collapses, it becomes 0.
  - If `K=0`, then collapsing is good!
  - If `K!=0`, collapsing is bad.

Is it possible to operate on *other* tiles to prevent collapse?
Yes. If doubling `grid[r][c]` would cause a collapse with neighbors, we might want to change neighbors first.
But we have limited `M`.
And changing neighbors takes steps.
Given "Hard" and `N=20`, maybe we just check the direct path?
Or maybe we check if we can break the cluster by modifying one neighbor?
Let's implement the **Direct Path Check**.
If direct path fails due to collapse, we check if we can modify a neighbor to break the cluster.
Modifying a neighbor costs steps.
We can use BFS to find the shortest sequence of "Modify Target" or "Modify Neighbor".
State: `(target_val, steps)`.
Actually, we just need to reach `K`.
We can model this as BFS.
Queue: `(current_grid, steps)`. Too big.
Queue: `(target_val, steps)`. Too simple.
We only care about the target and its immediate neighbors.
If target forms a cluster, we need to break it.
To break a cluster of 3, we need to change at least 1 neighbor (or the target itself, but we are constrained on target value).
So we might need to change a neighbor.
This looks like a local search.
Since `M` is likely small (or we want min steps), and `N` is small.
I'll implement a check:
1. Calculate min steps to transform `grid[r][c]` to `K` directly.
2. Simulate. If safe, return steps.
3. If unsafe (collapse), try to fix by modifying a neighbor.
   - Pick a neighbor that is part of the cluster.
   - Change it (1 step).
   - Then resume target transformation.
   - This is a BFS on the "Conflict Graph".
   - But simpler: Just try to change neighbors.

## Complexity
- **Time:** `O(M * Neighbors)`.
- **Space:** `O(N^2)`.
