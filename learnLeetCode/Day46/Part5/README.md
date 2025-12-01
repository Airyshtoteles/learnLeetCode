# Part 5: Phantom Knight Synchronization

## Problem Description

You control two Phantom Knights on an `N x M` grid.
*   **Start:** Knight 1 at `S1`, Knight 2 at `S2`.
*   **Goal:** Both Knights must reach the Target `T` **simultaneously**.
*   **Movement:** Both knights move simultaneously in L-shapes (standard Chess Knight moves).
    *   In one step, K1 moves to a neighbor, K2 moves to a neighbor.
    *   Staying in place is NOT allowed (unless specified, but standard BFS implies movement).

**Constraints:**
1.  **Distance Constraint:** At the end of every step, the Euclidean distance between K1 and K2 must be `<= D`.
2.  **Rune Synchronization:**
    *   The grid contains "Synchronization Runes" (Value 2).
    *   If **one** knight lands on a Rune (and the other does not), a **Synchronization Timer** starts (3 steps).
    *   The **other** knight must land on a Rune (any cell with value 2) within those 3 steps.
    *   If the timer expires without the second knight hitting a rune, the mission fails.
    *   If the second knight hits a rune within time, the timer clears.
    *   If both land on runes simultaneously, no timer starts (synced).

**Goal:** Find the minimum number of steps to reach the target.

## Approach

This is a Shortest Path problem on a composite state graph.

**State:** `(r1, c1, r2, c2, pending_who, timer)`
*   `r1, c1`: Position of Knight 1.
*   `r2, c2`: Position of Knight 2.
*   `pending_who`:
    *   `0`: No pending synchronization.
    *   `1`: Knight 1 triggered rune, waiting for Knight 2.
    *   `2`: Knight 2 triggered rune, waiting for Knight 1.
*   `timer`: Steps remaining (3, 2, 1).

**Transitions:**
For each step, generate all valid moves for K1 (max 8) and K2 (max 8). Total 64 combinations.
For each pair of moves `(n1, n2)`:
1.  Check bounds and walls (Value 1).
2.  Check Distance Constraint: `dist(n1, n2) <= D`.
3.  Update Rune State:
    *   `on_rune_1` = `grid[n1] == 2`
    *   `on_rune_2` = `grid[n2] == 2`
    *   Logic for next state:
        *   If `pending_who == 0`:
            *   If `on_rune_1` and `!on_rune_2`: Next `pending_who = 2`, `timer = 3`.
            *   If `!on_rune_1` and `on_rune_2`: Next `pending_who = 1`, `timer = 3`.
            *   Else: `pending_who = 0`.
        *   If `pending_who == 1` (Waiting for K1):
            *   If `on_rune_1`: Synced! `pending_who = 0`.
            *   Else: `timer -= 1`. If `timer == 0`, Invalid.
        *   If `pending_who == 2` (Waiting for K2):
            *   If `on_rune_2`: Synced! `pending_who = 0`.
            *   Else: `timer -= 1`. If `timer == 0`, Invalid.

**BFS:**
*   Queue stores `(steps, state)`.
*   Visited set stores `state`.
*   Target: `r1 == Tr, c1 == Tc, r2 == Tr, c2 == Tc`.

## Complexity
*   Grid `10 x 10`.
*   States: `100 * 100 * 3 * 4` ~ `120,000`.
*   Transitions: `64`.
*   Total Ops: `7.6 * 10^6`. Feasible.

