# Day 78: Advanced Mechanics & Optimization

This day focuses on complex game mechanics, graph constraints, and resource optimization.

## Problems

1.  **Delayed Damage Queue**
    *   **Concept**: Sorting, Prefix Sums.
    *   **Description**: Minimize time to reach damage threshold where damage is delayed by execution order.
    *   **Solution**: Sort damage descending. Execute largest first. Check cumulative damage at each time step.

2.  **Teleport Cooldown Graph**
    *   **Concept**: BFS with State.
    *   **Description**: Reach target in a graph where edges impose cooldowns on reusing the same cooldown value.
    *   **Solution**: BFS with state `(node, timers)`. Track blocked cooldowns.

3.  **Combo Counter Reset**
    *   **Concept**: Dynamic Programming, Array Manipulation.
    *   **Description**: Maximize non-decreasing substring length with one optional deletion.
    *   **Solution**: Compute `L[i]` (ending at i) and `R[i]` (starting at i). Maximize `L[i-1] + R[i+1]` if mergeable.

4.  **Rotating Laser Grid**
    *   **Concept**: Simulation, State Tracking.
    *   **Description**: Count unique cells visited by a laser that rotates every k steps.
    *   **Solution**: Simulate movement. Use a set of `(r, c, dir, step_mod)` to detect loops.

5.  **Resource Craft Loop**
    *   **Concept**: Greedy, Math.
    *   **Description**: Maximize final resource by applying division recipes in optimal order.
    *   **Solution**: Sort recipes descending (largest divisor first) to minimize loss from integer division floor.

6.  **Boss Revival Rule**
    *   **Concept**: Subset Sum, Partition.
    *   **Description**: Minimize attacks to kill boss with two phases (H and H/2).
    *   **Solution**: Iterate $k$ (number of attacks). Check if top $k$ attacks can be partitioned into two sets summing to $\ge H$ and $\ge H/2$ using Subset Sum (Bitset/DP).
