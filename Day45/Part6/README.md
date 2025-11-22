# Day 45 Part 6: Gravity-Shift Puzzle Platformer

## Problem Description

You are in a 2D grid map containing platforms (walls) and empty space.
*   **Start:** $S$
*   **Goal:** $G$
*   **Actions:**
    1.  **Jump/Move:** Move to an adjacent cell (Up, Down, Left, Right) if it's not a wall. Cost: 1 action.
    2.  **Gravity Shift:** Choose a direction (Up, Down, Left, Right). You "fall" in that direction until you hit a wall or the grid boundary. Cost: 1 action.
*   **Constraint:** You can use **Gravity Shift** at most **3 times**.
*   **Goal:** Reach $G$ with minimum total actions.

## Algorithm: BFS on State Space

We need to find the shortest path in a graph where nodes are states `(row, col, shifts_remaining)`.

### State
`State = (r, c, k)`
*   $r, c$: Current position.
*   $k$: Gravity shifts remaining (starts at 3).

### Transitions
From state $(r, c, k)$:
1.  **Standard Move:**
    *   For each neighbor $(nr, nc)$:
        *   If valid (in bounds, not wall):
            *   New State: $(nr, nc, k)$.
            *   Cost: $+1$.
2.  **Gravity Shift:**
    *   If $k > 0$:
        *   For each direction $d \in \{U, D, L, R\}$:
            *   Simulate "falling": Keep moving in direction $d$ until hitting a wall or boundary. Let the final position be $(fr, fc)$.
            *   New State: $(fr, fc, k-1)$.
            *   Cost: $+1$.

### Complexity
*   Grid size $M \times N$.
*   Max Shifts $K=3$.
*   States: $M \times N \times (K+1)$.
*   Edges: 4 (Move) + 4 (Shift) = 8 per state.
*   BFS is efficient enough.

## Implementation Details
*   `visited[r][c][k]` to avoid cycles and redundant processing.
*   Queue stores `(r, c, k, steps)`.
*   Input: Grid map.
