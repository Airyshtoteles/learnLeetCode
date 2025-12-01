# Day 45 Part 1: Time-Reversal Grid Combat

## Problem Description

You are navigating an $M \times N$ grid from $(0, 0)$ to $(M-1, N-1)$.
*   **Movement:** You can move Right or Down.
*   **Damage:** Each cell $(r, c)$ contains an enemy with $HP[r][c]$. When you enter a cell, you take damage equal to the enemy's HP.
*   **Time Reversal Ability:**
    *   You can choose **one** split point $(r, c)$ along your path.
    *   Let the path be $S \to \dots \to U \to \dots \to E$.
    *   The segment $S \to U$ is traversed normally.
    *   The segment $U \to E$ is subject to **Time Reversal**.
    *   **Effect:** The moves taken from $U$ to $E$ are the **reverse sequence** of the moves of a valid path from $U$ to $E$.
    *   **Benefit:** The damage taken on the Time-Reversed segment ($U \to E$) is **negated** (or effectively 0, as "HP is restored").
    *   **Constraint:** The path formed by the reversed moves must be a valid path (e.g., stay within grid boundaries, though for a rectangle grid with only Right/Down moves, any permutation is valid).
    *   **Goal:** Minimize Total Damage = Damage($S \to U$). (The suffix is free).

## Algorithm: Shortest Path with Suffix Optimization

Since the "Time Reversal" effectively makes the suffix damage 0, we want to maximize the length (or cost) of the suffix, or rather, minimize the cost of the prefix $S \to U$.

However, we must ensure that we can actually reach $E$ from $U$.
In a standard grid with only Right/Down moves, we can reach $E$ from any $U$ such that $U.r \le E.r$ and $U.c \le E.c$.
Since we only move Right/Down, any point we visit satisfies this.

So the problem reduces to:
**Find a node $U$ on the grid such that:**
1.  $U$ is reachable from $S$.
2.  $E$ is reachable from $U$.
3.  Minimize $Cost(S \to U)$.

Wait, if we minimize $Cost(S \to U)$, we should just pick $U = E$.
Then Cost is $Cost(S \to E)$.
If we pick $U = S$, Cost is $Cost(S \to S) = HP(S)$. Suffix $S \to E$ is free.
Total Damage = $HP(S)$.
This seems trivial if the suffix is truly free.

**Refined Interpretation for "Hard" Difficulty:**
Maybe the "Time Reversal" doesn't make it free, but **restores HP** to a base value?
*   Assumption: Enemy HP increases over time (e.g., $HP_{current} = HP_{base} + t$).
*   Normal traversal pays $HP_{base} + t$.
*   Reversed traversal pays $HP_{base}$.
*   We want to minimize total cost.

**Algorithm (Time-Dependent Weights):**
1.  Calculate `dist_start[r][c]`: Min cost to reach $(r, c)$ from Start, accounting for time-dependent damage.
    *   $Cost = HP[r][c] + steps$.
2.  Calculate `dist_end[r][c]`: Min cost to reach End from $(r, c)$ using **Base HP** (Time Reversal effect).
    *   This is a standard shortest path from $(r, c)$ to End on the static grid $HP$.
    *   We can compute this by running Dijkstra/BFS backwards from End to Start on the static graph.
3.  Iterate over all cells $(r, c)$:
    *   `Total = dist_start[r][c] + dist_end[r][c]`.
    *   Track minimum.

## Implementation Details
*   Grid size up to $100 \times 100$.
*   HP values integer.
*   Time penalty: +1 damage per step (assumption to make it non-trivial).
