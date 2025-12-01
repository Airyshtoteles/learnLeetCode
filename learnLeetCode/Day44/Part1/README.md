# Day 44 Part 1: Chrono Path Collapse

## Problem Description

You are given an $N \times M$ grid. Each cell $(i, j)$ has:
*   `cost[i][j]`: Energy required to enter this cell.
*   `timeGate[i][j]`: A list of specific time points (in seconds) when this cell ceases to exist (or kills you).

**Rules:**
1.  Start at $(0, 0)$ with initial Energy $E$ and time $t=0$.
2.  Target is $(N-1, M-1)$.
3.  Movement: Up, Down, Left, Right.
4.  Each move takes **1 second**.
5.  When moving to $(r, c)$, your energy decreases by `cost[r][c]`.
6.  If you enter $(r, c)$ at time $t_{arrival}$ and $t_{arrival}$ is present in `timeGate[r][c]`, you die.
7.  Energy must remain $\ge 0$.

**Goal:** Find the **minimum time** to reach $(N-1, M-1)$. Return -1 if impossible.

## Algorithm: BFS with State Pruning

Since edge weights (time) are uniform (1 second), we can use **BFS** to find the shortest path. However, we have an additional constraint: **Energy**.

### State
A naive BFS state would be `(row, col, energy)`. However, visiting the same cell with different energies can be redundant.

### Pruning Strategy
We want to minimize **Time**.
If we reach cell $(r, c)$ at time $t$ with energy $e$, and we have previously reached $(r, c)$ at time $t' \le t$ with energy $e' \ge e$, then the current path is strictly worse (slower and less/equal energy).

Since BFS explores layer by layer (increasing time $t$), we only need to track the **maximum energy** observed at each cell so far.
*   Let `max_energy[r][c]` store the max energy with which we have reached $(r, c)$.
*   Initialize `max_energy` with -1.
*   When trying to move to $(next\_r, next\_c)$ with `next_energy`:
    *   If `next_energy > max_energy[next_r][next_c]`:
        *   Update `max_energy[next_r][next_c] = next_energy`
        *   Push to queue.
    *   Otherwise, discard this path (we found a path to this cell that is faster or same speed but with more energy before).

### Complexity
*   **Time:** In the worst case, we might revisit cells if we find a path with higher energy. However, energy is bounded by $E$. The number of states is roughly $O(N \times M \times E)$ in the worst case, but with pruning, it's often much faster.
*   **Space:** $O(N \times M)$ for `max_energy` array.

## Implementation Details
*   **Queue:** Stores `(row, col, current_energy, current_time)`.
*   **Time Gates:** Store as a `set` or hash table for $O(1)$ lookup.
