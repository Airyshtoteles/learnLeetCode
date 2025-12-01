# Day 44 Part 4: Zero-Gravity Box Field

## Problem Description

You are in a 3D room of size $N \times N \times N$.
*   There are several boxes, each occupying a $1 \times 1 \times 1$ cell.
*   One box is special (ID = 1).
*   You can change gravity to one of 6 directions: $+x, -x, +y, -y, +z, -z$.
*   **Physics:** When gravity changes, **ALL** boxes fall in that direction until they hit the room boundary or another box.
*   **Goal:** Find the minimum number of gravity changes to move Box 1 to a specific target coordinate $(tx, ty, tz)$.

## Algorithm: BFS with Physics Simulation

This is a shortest path problem on the state space of box configurations.

### State
A state is defined by the positions of all boxes: `[(x1, y1, z1), (x2, y2, z2), ...]`.
*   Since boxes are distinct (at least Box 1 is), we maintain the order or IDs.
*   To check for visited states, we can hash this list of positions.

### Transitions (Gravity Change)
For each of the 6 directions:
1.  **Sort** the boxes based on the coordinate in the direction of fall.
    *   Example: Falling to $+x$ (increasing x). Sort boxes by $x$ descending (boxes with larger $x$ move first? No, boxes with larger $x$ are closer to the wall if wall is at $N$. If falling to $+x$, the one with largest $x$ hits the wall first. So process from largest $x$ to smallest $x$).
    *   Actually, if falling to $+x$ (limit $N-1$), the box at $x=N-1$ doesn't move. The box at $x=0$ moves last. So sort descending.
    *   If falling to $-x$ (limit $0$), sort ascending.
2.  **Simulate Fall:**
    *   Maintain a `occupied` set or grid for current positions.
    *   For each box in sorted order:
        *   Remove from `occupied`.
        *   Calculate new position: Move in direction until hit wall or occupied cell.
        *   Update position.
        *   Add to `occupied`.
3.  **Check Goal:** If Box 1 is at $(tx, ty, tz)$, return steps + 1.
4.  **Store State:** If new configuration is not visited, add to queue.

### Complexity
*   **Simulation:** $O(K \cdot N)$ where $K$ is number of boxes.
*   **BFS:** Number of reachable states is hard to estimate but typically "puzzle" complexity. With $N=30, K=300$, we rely on the fact that the solution (if exists) is short, or reachable states are sparse.
*   **Space:** Storing states can be memory intensive.

## Implementation Details
*   Use `tuple` of coordinates in Python for hashing.
*   Use `vector<tuple>` in C++.
