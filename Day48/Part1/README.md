# Part 1: Quantum Mirror Labyrinth

## Problem Description

You are in an `N x M` grid dungeon that exists in two parallel states: **Real World (R)** and **Mirror World (M)**.

*   You start at `(0, 0)` in the **Real World**.
*   You must reach `(N-1, M-1)` in the **Mirror World**.

**Mechanics:**
1.  **Movement:** You can move Up, Down, Left, Right to adjacent cells.
    *   A move is valid only if the destination cell value is `0` (Safe) in the **current world**.
    *   Cost of movement: **1**.
2.  **World Inversion:** The two worlds are binary inverses.
    *   If `Grid_R[i][j] == 0`, then `Grid_M[i][j] == 1` (Blocked).
    *   If `Grid_R[i][j] == 1`, then `Grid_M[i][j] == 0` (Safe).
3.  **Mirror Gates:** Some cells contain "Mirror Gates".
    *   At a gate at `(r, c)`, you can switch worlds (R -> M or M -> R).
    *   Switching costs `switch_cost`.
    *   **Crucial Rule:** You can ALWAYS switch at a gate, even if the destination cell in the other world would normally be '1' (Blocked). The Gate stabilizes the destination for you to stand on. However, you can only *leave* that cell to a neighbor if the neighbor is `0` in the current world.

**Input:**
*   `N`, `M`: Dimensions.
*   `Grid_R`: `N x M` matrix (0/1).
*   `Gates`: List of `[r, c, cost]`.

**Output:**
*   Minimum cost to reach `(N-1, M-1)` in World M. Return `-1` if impossible.

### Example

**Input:**
```text
N = 3, M = 3
Grid_R = [
  [0, 0, 1],
  [1, 0, 0],
  [1, 1, 0]
]
Gates = [[1, 1, 5]] (Gate at center, cost 5)
```

**Logic:**
*   Start (0,0) in R.
*   Path in R: (0,0)->(0,1)->(1,1). Cost 2.
*   At (1,1), we are at a Gate.
*   Switch to M. Cost 5. Total 7.
*   Now at (1,1) in M.
    *   Grid_M is inverse of Grid_R.
    *   Grid_R[1][1] is 0, so Grid_M[1][1] is 1.
    *   But we are ON the gate, so we are safe.
*   Move from (1,1) in M.
    *   Neighbors in M:
        *   (0,1): R=0 -> M=1 (Blocked)
        *   (1,0): R=1 -> M=0 (Safe)
        *   (1,2): R=0 -> M=1 (Blocked)
        *   (2,1): R=1 -> M=0 (Safe)
*   Move to (2,1) in M. Cost 1. Total 8.
*   From (2,1) in M, move to (2,2).
    *   (2,2) in R is 0 -> M is 1. Blocked?
    *   Wait, target is (2,2). If (2,2) is blocked in M, we can't reach it?
    *   Let's assume the target must be safe in M, or the target is a special case.
    *   In this example, R[2][2] is 0, so M[2][2] is 1.
    *   If the target is blocked, it's unreachable unless it's a Gate?
    *   Let's assume for this problem that the target is guaranteed to be 0 in M, or we just need to reach the coordinate.
    *   Actually, let's change the example so R[2][2] = 1, so M[2][2] = 0.

**Revised Example Grid:**
```text
Grid_R = [
  [0, 0, 1],
  [1, 0, 0],
  [1, 1, 1]  <-- (2,2) is 1, so M(2,2) is 0.
]
```
*   ... Move to (2,1) in M.
*   From (2,1) [M=0], move to (2,2) [M=0]. Cost 1. Total 9.

**Output:**
```text
9
```
