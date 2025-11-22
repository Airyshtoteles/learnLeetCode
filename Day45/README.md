# Day 45: 10 Hard Problems Challenge

This day focuses on solving 10 complex algorithmic problems involving advanced techniques like BFS on composite states, Simulation, Beam Search, and Bitmasking.

## Problems

1.  **Time Reversal** (Part 1)
    *   **Topic:** Graph Theory / BFS
    *   **Approach:** BFS on state `(position, time_reversed_boolean)`.

2.  **Domino Collapse** (Part 2)
    *   **Topic:** Simulation / DP
    *   **Approach:** Simulate forces or use DP to find stable state.

3.  **Evacuation with Rotating Bridges** (Part 3)
    *   **Topic:** Graph Theory / Dynamic Graph
    *   **Approach:** BFS with time-dependent edge weights (bridges rotate based on time).

4.  **Spell Deck Optimization** (Part 4)
    *   **Topic:** Combinatorics / Optimization
    *   **Approach:** Knapsack-like DP or Greedy approach depending on constraints.

5.  **Phantom Maze** (Part 5)
    *   **Topic:** BFS / State Space Search
    *   **Approach:** BFS on composite state `(player_pos, shadow_pos)`. Shadow moves inversely.

6.  **Gravity Shift** (Part 6)
    *   **Topic:** BFS / Simulation
    *   **Approach:** BFS where edges are "slides" in the current gravity direction. State includes `(pos, gravity_shifts_remaining)`.

7.  **Tower Defense** (Part 7)
    *   **Topic:** Simulation / Brute Force
    *   **Approach:** Brute force all combinations of tower placements (nCr) and simulate enemy waves.

8.  **Memory Tetris** (Part 8)
    *   **Topic:** Heuristic Search
    *   **Approach:** Beam Search to navigate the massive state space of grid configurations.

9.  **Battle Royale** (Part 9)
    *   **Topic:** Simulation
    *   **Approach:** Deterministic simulation of movement vectors and attack cycles.

10. **Echoing Doors** (Part 10)
    *   **Topic:** Dijkstra / Bitmasking
    *   **Approach:** Dijkstra on state `(x, y, z, door_mask)`. Passing a door toggles the state of other doors via bitmask operations.
