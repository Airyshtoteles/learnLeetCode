# Part 3: Shifting Realms Puzzle

## Problem Description

You exist in 3 parallel realms: **Realm A**, **Realm B**, and **Realm C**.
Each realm is an `N x N` grid where:
*   `1` represents a solid floor (walkable).
*   `0` represents a void (not walkable).

**Start:** `(0, 0)` in Realm A.
**Goal:** `(N-1, N-1)` in Realm C.

**Movement:**
1.  **Walk:** Move Up, Down, Left, Right within the *current* realm.
    *   Cost: `1`.
    *   Condition: Target cell must be `1` in the current realm.
2.  **Realm Shift:** Shift to the next realm in the cycle `A -> B -> C -> A`.
    *   Cost: `3`.
    *   Condition: The cell at your current coordinates `(r, c)` must be `1` in the *target* realm.

**Goal:** Find the minimum cost to reach the destination.

## Approach

This is a shortest path problem on a graph where the state is defined by `(row, col, realm_index)`.
*   `realm_index`: 0 (A), 1 (B), 2 (C).
*   Total nodes: `3 * N * N`.
*   Edges:
    *   Neighbors in grid: Weight 1.
    *   Next Realm: Weight 3.

**Algorithm:**
1.  Construct the 3 grids.
2.  Run Dijkstra's Algorithm starting from `(0, 0, 0)`.
3.  Target node is `(N-1, N-1, 2)`.
4.  If unreachable, return -1.

## Complexity
*   Nodes `V = 3 * N^2`.
*   Edges `E = 4V (move) + V (shift) = 5V`.
*   Dijkstra: `O(V log V)`.
*   With `N=50`, `V=7500`, very fast.

