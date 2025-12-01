# Day 44 Part 5: Binary Dungeon: Parity Doors

## Problem Description

You are in a dungeon represented as a graph with $N$ rooms and $M$ edges.
*   Each edge has a type $b \in \{0, 1\}$.
*   You carry a **Parity Key**, initially $0$.
*   **Traversal Rule:** When you cross an edge of type $b$, your key changes: `new_key = old_key XOR b`.
*   **Room Constraints:**
    *   Some rooms require `key == 0` to enter.
    *   Some rooms require `key == 1` to enter.
    *   Some rooms have no restriction.
*   **Goal:** Find the shortest path (minimum edges) from Start to Goal.

## Algorithm: BFS on State Graph

This is a shortest path problem on a graph where each node is split into two states based on the parity key.

### State
`State = (u, parity)`
*   $u$: Current room ID ($0 \dots N-1$).
*   $parity$: Current key value ($0$ or $1$).

### Transitions
From state $(u, p)$:
*   For each neighbor $v$ connected by edge of type $w$:
    *   Calculate `next_p = p XOR w`.
    *   **Check Constraint:** Does room $v$ allow parity `next_p`?
        *   If $v$ requires 0 and `next_p` is 1: Invalid.
        *   If $v$ requires 1 and `next_p` is 0: Invalid.
        *   Otherwise: Valid.
    *   If valid and `dist[v][next_p]` is unvisited:
        *   `dist[v][next_p] = dist[u][p] + 1`
        *   Push $(v, next\_p)$ to queue.

### Complexity
*   **Nodes:** $2N$ (since parity is 0 or 1).
*   **Edges:** $2M$.
*   **Time:** $O(N + M)$ using BFS.
*   **Space:** $O(N)$ for distance array.

## Implementation Details
*   `dist[N][2]` array.
*   Adjacency list `adj[u] = [(v, w), ...]`.
*   `constraints[u]` array: -1 (None), 0 (Requires 0), 1 (Requires 1).
