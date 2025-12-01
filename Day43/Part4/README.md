# Day 43 Part 4: Parallel World Platformer

## Problem Description

You are navigating a multiverse with two parallel worlds: **Normal World (0)** and **Inverted World (1)**.
Both worlds share the same grid dimensions $N \times M$.
You start at 'S' in World 0. You need to reach 'E' (which exists in the same coordinate in both worlds, or maybe just reach the coordinate). The problem says "reach E (any world)".

### Movement Rules:
1.  **Standard Move:** Up, Down, Left, Right. Cost = 1.
    *   Valid only if the target cell in the *current world* is not a wall ('#').
2.  **Dimension Rift:**
    *   Specific coordinates contain a "Rift".
    *   If you are standing on a Rift, you can teleport to the *same coordinate* in the *other world*.
    *   Cost = 0.
    *   Note: The terrain in the other world might be different. A wall in World 0 might be a path in World 1.

### Input Format
*   `N M` (Dimensions)
*   `Grid 0` (N lines of M chars)
*   `Grid 1` (N lines of M chars)
*   `K` (Number of Rifts)
*   `K` lines of `r c` (Rift coordinates)

### Output Format
*   Minimum steps to reach 'E'. If unreachable, return -1.

## Algorithm: 0-1 BFS (Breadth-First Search)

Since the edge weights are either 0 (Teleport) or 1 (Move), we can use **0-1 BFS** (using a Deque) to find the shortest path efficiently in $O(N \times M)$.

### State
`dist[r][c][world]` stores the minimum distance to reach cell `(r, c)` in `world` (0 or 1).

### Transitions
1.  **Move (Cost 1):**
    *   For each neighbor `(nr, nc)`:
    *   If `grid[world][nr][nc] != '#'` and `dist[nr][nc][world] > dist[r][c][world] + 1`:
        *   `dist[nr][nc][world] = dist[r][c][world] + 1`
        *   `deque.push_back((nr, nc, world))`

2.  **Teleport (Cost 0):**
    *   If `(r, c)` is a Rift:
    *   `next_world = 1 - world`
    *   If `grid[next_world][r][c] != '#'` (Wait, can we teleport into a wall? Usually no. Assuming we can only teleport if the destination is safe. Or maybe we teleport and *then* check? Usually "terrain... might be different" implies we land on the terrain of the other world. If it's a wall, we can't be there.)
    *   Let's assume we can only teleport if `grid[next_world][r][c] != '#'`.
    *   If `dist[r][c][next_world] > dist[r][c][world]`:
        *   `dist[r][c][next_world] = dist[r][c][world]`
        *   `deque.push_front((r, c, next_world))`

### Complexity
*   **Time:** $O(N \times M)$ - Each state (cell + world) is processed once.
*   **Space:** $O(N \times M)$ - Distance array.

## Implementation Details
*   Use `collections.deque` in Python.
*   Use `std::deque` in C++.
*   Initialize `dist` with Infinity.
