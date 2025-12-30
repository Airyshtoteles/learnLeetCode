# Day 76: Game Mechanics & Optimization

This day focuses on optimizing game mechanics, graph traversal, and resource management.

## Problems

1.  **Damage Over Time Stack**
    *   **Concept**: Greedy, Optimization.
    *   **Description**: Calculate minimum time to reach total damage H using stackable DoTs.
    *   **Solution**: Sort DoTs descending. Iterate number of active DoTs $k$. Calculate time needed for each $k$ and find minimum.

2.  **Portal Permutation Jump**
    *   **Concept**: Graph Theory, Cycles.
    *   **Description**: Determine if target is reachable by breaking exactly one portal in a permutation graph.
    *   **Solution**: Decompose into cycles. Check if breaking a portal in start cycle can connect to target cycle.

3.  **Stagger Meter Drain**
    *   **Concept**: Simulation, Greedy.
    *   **Description**: Maximize stuns given attack sequence and stagger threshold.
    *   **Solution**: Simulate attacks. Reset meter immediately upon reaching threshold to maximize future stuns.

4.  **Dynamic Arena Partition**
    *   **Concept**: Reachability, Speed/Time.
    *   **Description**: Determine if enemy can be isolated from player using walls placed over time.
    *   **Solution**: Check if wall placement time $t$ is less than time for enemy to cross arena $L$.

5.  **Achievement Chain Reaction**
    *   **Concept**: Topological Sort, Graph.
    *   **Description**: Determine if all achievements are reachable given dependencies and bonuses.
    *   **Solution**: Modified Topological Sort where bonuses reduce in-degree of specific nodes.

6.  **Replay Time Scaling**
    *   **Concept**: Number Theory, Reachability.
    *   **Description**: Determine if total time T is achievable by scaling segment durations.
    *   **Solution**: Check if $T$ is greater than minimum possible sum (scaling all to 1). Heuristic based on unbounded knapsack properties.
