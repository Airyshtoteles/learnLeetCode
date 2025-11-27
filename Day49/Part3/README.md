# Day 49 Part 3: Time-Shifted Labyrinth

## Problem Description
You are navigating a labyrinth represented by an `N x M` grid. Each cell `(r, c)` has a time-shift value `T[r][c]`.
You start at `(0, 0)` at `time = 0`.
You can move up, down, left, or right. Each move takes 1 unit of time.
However, a cell `(r, c)` is **blocked** at time `t` if `(t + T[r][c]) % K == 0`.
You can wait at your current cell (taking 1 unit of time) if you wish, but you must check if your *current* cell becomes blocked at `t+1`.

Find the minimum time to reach `(N-1, M-1)`. If impossible, return -1.

## Example
**Input:**
```
Grid = [[1, 2], [3, 4]]
K = 3
```
Start (0,0). T[0][0] = 1.
Time 0: Check if (0,0) is blocked. (0 + 1) % 3 = 1 != 0. Safe.
Move to (0,1). T[0][1] = 2. Time becomes 1.
Check if (0,1) blocked at t=1: (1 + 2) % 3 = 0. BLOCKED. Cannot move there.

## Approach: BFS with Modulo State
- **State:** `(r, c, time % K)` is NOT sufficient because we need total time for the answer, but for *visitation* logic, `(r, c, time % K)` is sufficient to avoid cycles?
- Actually, since we want *minimum* time, standard BFS works.
- State for `visited` set: `(r, c, time % K)`. If we reach the same cell at the same modulo time with a higher total time, it's suboptimal.
- **Transitions:**
  1. Move to neighbors `(nr, nc)`. New time `t+1`. Check if `(t+1 + T[nr][nc]) % K == 0`.
  2. Wait at `(r, c)`. New time `t+1`. Check if `(t+1 + T[r][c]) % K == 0`.

## Complexity
- **Time:** O(N * M * K).
- **Space:** O(N * M * K).
