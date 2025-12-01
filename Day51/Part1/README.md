# Day 51 Part 1: Crystal Labyrinth Teleportation

## Problem Description
You are in an `n x m` grid with:
- `.`: Empty space
- `#`: Wall
- `S`: Start
- `E`: Exit
- `T`: Teleport (all `T`s are connected)
- `1-9`: Crystals with values

**Rules:**
- Move Up, Down, Left, Right (1 step).
- Teleport from `T` to any other `T` (0 steps, but effectively moving to a T takes 1 step, then instant transport).
- Collect crystals max once.
- Max `K` steps.
- Goal: Maximize total crystal value collected before reaching `E`.

## Approach
We use **BFS** with state `(r, c, mask)`.
- `mask`: Bitmask representing collected crystals.
- `dist[r][c][mask]`: Minimum steps to reach `(r, c)` with `mask`.
- Since we want to maximize value within `K` steps, finding the min steps for each state allows us to check feasibility.
- Finally, iterate over all states `(E_r, E_c, mask)` where `dist <= K` and find max value of `mask`.

**Teleportation Handling:**
- All `T` cells are effectively adjacent.
- When at a `T`, we can move to any neighbor of *any* `T` in 1 step?
- Or we move to another `T` and then move out?
- "Teleport tidak menghitung langkah".
- So if we are at `T1`, we are instantly at `T2`, `T3`...
- This means all `T` cells are merged into a single super-node or connected with weight 0.
- In BFS, if we reach a `T`, we can add all other `T`s to the queue with the same distance (if not visited).

**State Space:**
- Grid: `N x M`.
- Mask: `2^C` where `C` is number of crystals (max 9).
- Total states: `N * M * 512`.
- With `N, M <= 50`, this is `2500 * 512 ≈ 1.28e6`. Feasible.

## Complexity
- **Time:** `O(N * M * 2^C)`.
- **Space:** `O(N * M * 2^C)`.
