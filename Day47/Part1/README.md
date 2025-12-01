# Part 1: Echo of the Mirror Boss

## Problem Description

You are in an `N x M` grid.
*   **Player Start:** `(sx, sy)`
*   **Boss Start:** `(bx, by)`
*   **Target:** `(tx, ty)`
*   **Grid:** `0` = Empty, `1` = Wall.

**Mechanics:**
*   You move in 4 directions: Up, Down, Left, Right.
*   The Boss **mirrors** your movement:
    *   You move `(dx, dy)` -> Boss moves `(-dx, -dy)`.
    *   Example: You move Right `(0, 1)`, Boss moves Left `(0, -1)`.
    *   Example: You move Up `(-1, 0)`, Boss moves Down `(1, 0)`.

**Constraints:**
*   A move is valid ONLY IF:
    1.  Your new position is within bounds and not a wall.
    2.  The Boss's new position is within bounds and not a wall.
*   If either condition fails, the move cannot be taken (or results in death).

**Goal:**
Find the minimum number of steps for the **Player** to reach the Target `(tx, ty)`. The Boss's final position does not matter, as long as it survives the journey.

## Approach

This is a Shortest Path problem on a composite state graph.

**State:** `(px, py, bx, by)`
*   `px, py`: Player coordinates.
*   `bx, by`: Boss coordinates.

**Transitions:**
From state `(px, py, bx, by)`, try all 4 moves `(dx, dy)` in `[(0,1), (0,-1), (1,0), (-1,0)]`.
*   `npx = px + dx`, `npy = py + dy`
*   `nbx = bx - dx`, `nby = by - dy`
*   Check validity:
    *   `0 <= npx < N`, `0 <= npy < M`, `grid[npx][npy] == 0`
    *   `0 <= nbx < N`, `0 <= nby < M`, `grid[nbx][nby] == 0`
*   If valid, add `(npx, npy, nbx, nby)` to queue.

**BFS:**
*   Start: `(sx, sy, bx, by)` with distance 0.
*   Target: Any state where `px == tx` and `py == ty`.
*   Visited: Keep track of `(px, py, bx, by)` to avoid cycles.

## Complexity
*   Grid size `N, M`. Max `N, M <= 40` (typical for hard grid problems).
*   States: `(N*M)^2`. For `20x20`, `400^2 = 160,000`. Feasible.
*   For `40x40`, `1600^2 = 2.56 * 10^6`. Feasible.

