# Day 49 Part 5: Gravity Flip Duel

## Problem Description
You are in a 2D grid room filled with empty space (`.`), walls (`#`), a start point `S`, and a target `T`.
Gravity initially pulls you **Down**.
You can perform two types of actions:
1. **Walk:** Move perpendicular to the current gravity direction if you are supported by a wall "below" you (relative to gravity). Walking takes **0 cost**.
   - If you walk off a ledge (no support), you **fall** in the direction of gravity until you hit a wall or the boundary.
2. **Flip Gravity:** Change gravity to any of the 4 cardinal directions (Up, Down, Left, Right). This costs **1 energy**.
   - After flipping, you immediately **fall** in the new gravity direction until you hit a wall.

Find the **minimum energy** (gravity flips) required to reach the target `T`.

## Example
**Input:**
```
S . . . .
# # # . #
. . . . T
# # # # #
```
Start at (0,0). Gravity Down.
1. Fall to (1,0) (on top of wall).
2. Walk Right to (1,2).
3. Walk Right to (1,3) -> No support below (2,3) is empty. Fall Down to (3,3).
4. Now at (3,3). Gravity Down.
5. Walk Right to (3,4).
6. Target is at (2,4). We are at (3,4).
7. Flip Gravity UP (Cost 1). Fall Up to (2,4) (hit T? or hit wall above?).
   - If T is just a point in space, we pass through it?
   - Let's assume we stop if we hit T or a wall.
   - If we hit T, we win.

## Approach: Dijkstra / 0-1 BFS
- **State:** `(r, c, gravity_dir)`
- **Transitions:**
  1. **Walk:** Check neighbors perpendicular to `gravity_dir`.
     - If neighbor is wall: blocked.
     - If neighbor is empty:
       - Check support (cell in `gravity_dir` from neighbor).
       - If support exists (wall), move to neighbor. Cost 0.
       - If no support, **Fall** from neighbor in `gravity_dir`. Cost 0.
  2. **Flip:** Change `gravity_dir` to new `dir`.
     - **Fall** from current `(r, c)` in `new_dir`. Cost 1.

- **Falling Logic:**
  - Move in `gravity_dir` until hitting a wall or boundary.
  - If we pass `T` or land on `T`, we win? Let's say we stop at `T` if we hit it.
  - Otherwise, stop at the cell *before* the wall.

## Complexity
- **Time:** O(N * M * 4 * max(N, M)). Falling takes O(N) or O(M).
- **Space:** O(N * M * 4).
