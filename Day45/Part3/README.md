# Day 45 Part 3: Monster Evacuation With Rotating Bridges

## Problem Description

You are given a graph with $N$ nodes and $M$ edges.
*   **Rotating Bridges:** Some edges are "rotating bridges" that are only active (passable) when `current_time % k == 0`.
*   **Monsters:** There are several monsters at specific nodes, each with a `deadline`.
*   **Task:** For each monster, you must travel from `Start` to `MonsterNode` and then back to `Start`.
*   **Constraint:** The total time for a trip (Start $\to$ Monster $\to$ Start) must be $\le$ `deadline`.
*   **Goal:** Determine if all monsters can be saved. If yes, return the minimum time required (assuming parallel squads or max of individual times). If not, return -1.
    *   *Assumption:* We treat each monster independently (parallel rescue squads). If sequential was required, it would be a TSP variant which is much harder. Given "Hard" but usually "Evacuation" implies checking feasibility for all.

## Algorithm: Dijkstra with Dynamic Edge Weights

For each monster, we need the shortest path from Start to Monster and Monster to Start.
Since the graph is undirected (usually), $Start \to Monster$ is same as $Monster \to Start$ in distance, but **Wait Times** depend on arrival time.
So $Cost(A \to B)$ might differ from $Cost(B \to A)$ if we arrive at different times.

### Dynamic Edge Weight
*   **Normal Edge:** Weight $W$.
*   **Rotating Bridge:** Weight $W$, Period $K$.
    *   Can only enter at time $t$ if $t \% K == 0$.
    *   If we arrive at $t$, we must wait until next multiple of $K$.
    *   Wait time = $(K - (t \% K)) \% K$.
    *   Total time to cross = Wait + $W$.

### Strategy
1.  Run Dijkstra from `Start` to find `dist_from_start[u]`.
    *   State: `min_time` to reach `u`.
    *   When relaxing edge $(u, v)$:
        *   Calculate arrival at $u$ ($t_u$).
        *   Calculate wait time for edge $(u, v)$.
        *   $t_v = t_u + \text{wait} + W$.
2.  For each monster at $M_i$:
    *   We have `time_to_monster = dist_from_start[M_i]`.
    *   Now we need `time_back_to_start`.
    *   Run Dijkstra from $M_i$ to `Start` starting at `time_to_monster`.
    *   Total time = Arrival at Start.
    *   Check if Total Time $\le$ Deadline.
3.  Optimization:
    *   If $N$ is small, we can run Dijkstra for each monster.
    *   If $N$ is large, maybe we can't run Dijkstra for every monster?
    *   But wait times depend on absolute time.
    *   So we likely need to run a simulation/search for each monster.

## Complexity
*   $O(NumMonsters \cdot E \log V)$.
*   If $NumMonsters$ is large, this might be slow. But usually "several monsters" implies a manageable number.

## Implementation Details
*   `Start` node is 0.
*   Edges: `(u, v, w, k)` where $k=1$ means always active (since $t \% 1 == 0$ is always true).
