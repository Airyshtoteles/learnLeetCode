# Part 1: Time-Reversal Dungeon Pathfinding

## Problem Description

You are in an `N x M` dungeon grid.
*   `cost[i][j]`: Energy required to enter cell `(i, j)`.
*   `trap[i][j]`: 1 if the cell is a Time Trap, 0 otherwise.

**Mechanics:**
*   Movement: Up, Down, Left, Right.
*   **Time Trap:** If you enter a Time Trap:
    *   Your accumulated energy cost resets to 0.
    *   Your position remains at the trap.
    *   Effectively, this allows you to start a new path from the trap with 0 cost.

**Goal:**
Find the minimum energy required to reach `(N-1, M-1)` from `(0, 0)`.

**Constraints:**
*   `1 <= N, M <= 40`
*   `cost[i][j] <= 10^6`
*   Max 3 Time Traps.

## Approach

The "Time Reversal" mechanic essentially creates potential new starting points. Since the cost resets to 0 upon entering a trap, the total cost of a path that uses a trap is simply the cost of the segment *after* the last visited trap.

Therefore, the problem reduces to finding the shortest path from a set of potential starting points to the destination `(N-1, M-1)`.

The potential starting points are:
1.  The original Start `(0, 0)`.
2.  Any Trap `T` that is reachable from the Start (or from another reachable Trap). Since the grid is fully connected (unless costs are infinite, which isn't stated), all Traps are reachable.

**Algorithm:**
1.  Run Dijkstra's Algorithm from `Start (0,0)` to find the minimum cost to reach `End (N-1, M-1)` and all Traps.
    *   Let `Dist(U, V)` be the min cost to go from U to V.
    *   Base Answer = `Dist(Start, End)`.
2.  Identify all Trap locations `T1, T2, ... Tk`.
3.  For each Trap `Ti`:
    *   Check if `Ti` is reachable from `Start` (Cost < Infinity).
    *   If reachable, run Dijkstra from `Ti` to find `Dist(Ti, End)`.
    *   Update Answer: `Ans = min(Ans, Dist(Ti, End))`.
4.  Return `Ans`.

**Complexity:**
*   Dijkstra runs in `O(E log V)`. Here `V = N*M`, `E = 4*N*M`.
*   We run Dijkstra at most `1 + NumTraps` times.
*   With `N, M <= 40`, `V = 1600`. `NumTraps <= 3`.
*   Total operations roughly `4 * 1600 * log(1600)`, which is very fast.

## Edge Cases
*   Start is a trap: Cost resets immediately? (Assume yes, effectively same as starting with 0).
*   End is a trap: Cost to enter is paid, then reset? But we reached the goal. Usually goal check happens after entry. If we enter and cost resets, total cost is 0?
    *   Interpretation: We pay the cost to *enter*. If we are at End, we are done. The reset happens *after* entry. But if we are done, the cost we just paid matters.
    *   However, if we treat the trap as a start point, the cost *from* the trap to End is what matters.
    *   If End is a trap, and we reach it, the cost is `PathCost`. The reset is irrelevant because we finished.
