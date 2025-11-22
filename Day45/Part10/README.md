# Day 45 Part 10: Labyrinth of Echoing Doors

## Problem Description

You are in a 3D Maze ($X \times Y \times Z$).
*   **Start:** $S$. **Goal:** $G$.
*   **Cells:** Empty, Wall, or Door.
*   **Doors:**
    *   Each door has an ID ($0 \dots K-1$).
    *   Each door has an initial state (Open/Closed).
    *   **Echo Effect:** Passing through Door $i$ toggles the state of a set of other doors (defined by a mask or list).
    *   You can only pass through a door if it is currently **Open**.
*   **Goal:** Reach $G$ passing through the **minimum number of doors**.
    *   Walking through empty cells costs 0.
    *   Walking through a door costs 1.

## Algorithm: 0-1 BFS (Dijkstra)

Since edge weights are 0 (empty) or 1 (door), we can use 0-1 BFS (Deque) or Dijkstra.
Given the state complexity, Dijkstra is safer/easier to implement with a Priority Queue.

### State
`State = (x, y, z, mask)`
*   $x, y, z$: Current position.
*   $mask$: Bitmask representing the state of all $K$ doors ($1=$ Open, $0=$ Closed).

### Transitions
From $(x, y, z, mask)$:
1.  **Move to Neighbor $(nx, ny, nz)$:**
    *   If Wall: Invalid.
    *   If Empty:
        *   New State: $(nx, ny, nz, mask)$.
        *   Cost: $+0$.
    *   If Door $d$:
        *   Check if `(mask >> d) & 1`:
            *   If Open:
                *   New Mask: `mask ^ effect[d]`. (Toggle affected doors).
                *   New State: $(nx, ny, nz, new\_mask)$.
                *   Cost: $+1$.
            *   If Closed: Invalid.

### Complexity
*   Grid size $V = X \cdot Y \cdot Z$.
*   Doors $K \le 16$ (Assumption for bitmask).
*   States: $V \cdot 2^K$.
*   Edges: 6 per state.
*   If $K$ is small (e.g., 10), $2^{10} = 1024$. $V=1000$. Total $10^6$ states. Feasible.

## Implementation Details
*   Input: Grid, Door definitions (Location, ID, Initial State, Effect Mask).
*   Priority Queue: `(cost, x, y, z, mask)`.
*   `dist[x][y][z][mask]` array initialized to INF.
