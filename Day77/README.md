# Day 77: Time Paradoxes & Resource Management

This day focuses on time-based constraints, resource allocation, and graph traversal with dynamic conditions.

## Problems

1.  **Checkpoint Time Paradox**
    *   **Concept**: Time Constraints, Greedy.
    *   **Description**: Determine if all checkpoints can be reached given strict arrival time limits.
    *   **Solution**: Check if $i \le t[i]$ for all checkpoints $i$.

2.  **Boss Shield Rotation**
    *   **Concept**: Greedy, Scheduling.
    *   **Description**: Determine if boss shields can be destroyed by assigning attacks to rotating shield slots.
    *   **Solution**: Sort shields by average damage required per slot. Assign largest available attacks to the most demanding shields.

3.  **Party Formation Lock**
    *   **Concept**: Greedy, Array Manipulation.
    *   **Description**: Minimize removals to prevent adjacent identical elements.
    *   **Solution**: Count adjacent duplicates. For each pair of duplicates, one removal is necessary.

4.  **Infinite Loot Generator**
    *   **Concept**: Simulation, Sequence Analysis.
    *   **Description**: Calculate total loot value where value doubles if smaller than previous.
    *   **Solution**: Simulate the process. If $v[i] < v[i-1]$, add $2 \times v[i]$, else add $v[i]$.

5.  **Skill Memory Limit**
    *   **Concept**: Optimization, Set Theory.
    *   **Description**: Minimize cooldowns by reordering skills with limited memory.
    *   **Solution**: Group identical skills together. Total cost equals the number of unique skills.

6.  **Map Collapse Frontier**
    *   **Concept**: Multi-source BFS, Pathfinding.
    *   **Description**: Find a path to target while avoiding spreading collapse.
    *   **Solution**: Run BFS for collapse spread to get danger times. Run BFS for player, moving only if arrival time is strictly less than collapse time.
