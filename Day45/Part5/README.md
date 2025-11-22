# Day 45 Part 5: Phantom Maze With Shadow Player

## Problem Description

You are navigating an $M \times N$ maze.
*   **Player:** Starts at $S_p$, Goal is $G_p$.
*   **Shadow:** Starts at $S_s$. Moves in a separate "parallel" maze (or same dimensions).
*   **Movement:**
    *   When Player moves **Up**, Shadow moves **Down**.
    *   When Player moves **Down**, Shadow moves **Up**.
    *   When Player moves **Left**, Shadow moves **Right**.
    *   When Player moves **Right**, Shadow moves **Left**.
*   **Constraints:**
    *   Both Player and Shadow must move into valid cells (within bounds, not walls). If a move is blocked for *either*, the move is invalid (cannot be taken).
    *   **Linked Cells:** A list of pairs $((r1, c1), (r2, c2))$ is given. If Player is at $(r1, c1)$ and Shadow is at $(r2, c2)$, you lose immediately.
*   **Goal:** Find the minimum number of steps for the Player to reach $G_p$.

## Algorithm: BFS on State Space

This is a shortest path problem on a graph where each node is a composite state of the Player and Shadow positions.

### State
`State = (player_row, player_col, shadow_row, shadow_col)`

### Transitions
From state $(pr, pc, sr, sc)$, try all 4 directions $d \in \{U, D, L, R\}$:
1.  Calculate `next_pr`, `next_pc` based on $d$.
2.  Calculate `next_sr`, `next_sc` based on $inverse(d)$.
3.  **Validity Check:**
    *   `next_p` must be within bounds and not a wall in Player's maze.
    *   `next_s` must be within bounds and not a wall in Shadow's maze.
    *   (Assumption: If one is blocked, the move is impossible. Alternative interpretation: The one blocked stays put? Usually "mimic" puzzles require both to move or one stays. I will assume **strict lockstep**: if one is blocked, the move cannot be made).
4.  **Safety Check:**
    *   The pair `((next_pr, next_pc), (next_sr, next_sc))` must NOT be in the `Linked` set.
5.  If valid and safe and not visited, add to Queue.

### Complexity
*   States: $(M \times N)^2$.
*   Edges per state: 4.
*   For $20 \times 20$ grid, states $\approx 160,000$. BFS is very fast.

## Input Format (Assumed)
1.  $M, N$
2.  Grid 1 (Player Maze)
3.  Grid 2 (Shadow Maze) - *Prompt says "maze paralel", implying potentially different layout.*
4.  $S_p, G_p$ (Player Start/Goal)
5.  $S_s$ (Shadow Start)
6.  $K$ (Number of linked pairs)
7.  $K$ lines of linked pairs: $r1 \ c1 \ r2 \ c2$

## Implementation Details
*   Use a `visited` set/array `visited[pr][pc][sr][sc]`.
*   Queue for BFS.
