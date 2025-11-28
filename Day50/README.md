# Day 50: Advanced Algorithmic Challenges

Today's focus was on solving 5 "Hard" algorithmic problems involving complex state transitions, dynamic programming, and graph theory.

## Problems

### Part 1: Time-Reversal Dungeon
- **Concept:** Greedy with Heuristic / Optimization.
- **Description:** Minimizing weighted sum of monster powers by reversing segments.
- **Solution:** Greedy approach targeting largest inversions.

### Part 2: Rogue Chess - Maximum Capture Chain
- **Concept:** Longest Path in DAG (Backtracking).
- **Description:** Finding the longest capture chain for a Rogue Knight.
- **Solution:** DFS with backtracking to explore all valid capture sequences.

### Part 3: The Shifting Maze of Echoes
- **Concept:** Dijkstra on Dynamic Grid.
- **Description:** Navigating a maze where walls shift right over time.
- **Solution:** Dijkstra's algorithm with state `(flips, time, r, c)`.

### Part 4: Spell Weaving Arena
- **Concept:** Dynamic Programming (Scheduling).
- **Description:** Maximizing spell power with cooldowns over time T.
- **Solution:** DP `dp[t]` maximizing power at time `t`.

### Part 5: Quantum Tile Collapse
- **Concept:** BFS on Grid State.
- **Description:** Reaching a target value by doubling tiles, with cluster collapse mechanics.
- **Solution:** BFS exploring operations on target and relevant neighbors.

## Structure
Each part has its own directory with:
- `README.md`: Detailed problem analysis.
- `*.py`: Python solution.
- `*.cpp`: C++ solution.
