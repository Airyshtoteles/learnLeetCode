# Day 44 Part 3: Twin Dungeon Mirrors

## Problem Description

You control two characters simultaneously in two identical dungeons (Grid A and Grid B).
*   **Input:** Grid dimensions $N \times M$, Grid layout (Walls '#', Floor '.', Start 'S', Goal 'G').
    *   Note: The problem says "Two identical dungeons", but usually "S" and "G" might be at different positions for Char A and Char B. Or maybe the map is the same, but they start at different S's?
    *   "S = start (dua dungeon punya S masing-masing)". This implies distinct start positions.
    *   "G = goal (dua dungeon punya G masing-masing)". Distinct goals.
*   **Movement:** When you press a direction (Up, Down, Left, Right), **BOTH** characters attempt to move in that direction.
*   **Collision:** If a character hits a wall ('#'), they **stay in place**. The other character continues moving if their path is clear.
*   **Goal:** Find the minimum number of steps such that **BOTH** characters are standing on their respective 'G' cells **at the same time**.

## Algorithm: BFS on Product Graph

This is a shortest path problem on a graph where each node represents the combined state of both characters.

### State
`State = (row_A, col_A, row_B, col_B)`
*   $(row_A, col_A)$: Position of Character A.
*   $(row_B, col_B)$: Position of Character B.

### Transitions
From state $(r_A, c_A, r_B, c_B)$, for each direction $D \in \{U, D, L, R\}$:
1.  Calculate target for A: $(tr_A, tc_A) = (r_A + dr, c_A + dc)$.
    *   If $(tr_A, tc_A)$ is a wall or out of bounds, new pos for A is $(r_A, c_A)$.
    *   Else, new pos for A is $(tr_A, tc_A)$.
2.  Calculate target for B: $(tr_B, tc_B) = (r_B + dr, c_B + dc)$.
    *   If $(tr_B, tc_B)$ is a wall or out of bounds, new pos for B is $(r_B, c_B)$.
    *   Else, new pos for B is $(tr_B, tc_B)$.
3.  New State: $(new\_r_A, new\_c_A, new\_r_B, new\_c_B)$.
4.  Cost: +1 step.

### Complexity
*   **States:** $O(N^2 M^2)$. For $N, M = 20$, states $\approx 160,000$. For $N, M = 50$, states $\approx 6.25 \times 10^6$. BFS is feasible.
*   **Time:** $O(N^2 M^2)$.
*   **Space:** $O(N^2 M^2)$ for visited array/distance map.

## Implementation Details
*   Use a 4D array `dist[N][M][N][M]` initialized to -1 or Infinity.
*   Queue for BFS.
