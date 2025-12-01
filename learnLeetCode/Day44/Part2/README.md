# Day 44 Part 2: Spiral Arena Summoner

## Problem Description

You are in a circular arena. There are $K$ monsters at various positions $(x, y)$.
*   Every second, each monster moves 1 unit towards the center $(0, 0)$.
*   You can summon **1 barrier per second** at any point on the arena.
*   A barrier at a specific angle destroys all monsters aligned with that angle (Ray Gun model).
*   Goal: Prevent any monster from reaching the center (distance $\le 0$).
*   Return the **minimum number of barriers** needed, or -1 if impossible.

## Algorithm: Greedy Scheduling

### 1. Grouping by Angle
Monsters coming from the same direction (collinear with origin) can be destroyed by a single barrier placed at that angle.
*   We represent the direction of a monster at $(x, y)$ by the simplified vector $(x', y') = (x/\gcd, y/\gcd)$.
*   Group all monsters by this unique direction vector.

### 2. Determining Deadlines
For each group (angle), we only care about the **closest monster** (the one that will reach the center first).
*   Distance $d = \sqrt{x^2 + y^2}$.
*   The monster reaches the center in $\lceil d \rceil$ seconds.
*   We must summon a barrier for this angle at some time $t < \lceil d \rceil$.
*   Let the deadline for an angle be $D_{angle} = \lceil \min(d) \text{ for monsters in angle} \rceil$.

### 3. Scheduling
We have a set of tasks (angles), each with a deadline. Each task takes 1 second.
*   Sort all deadlines in **ascending order**.
*   Try to assign time slots $t = 0, 1, 2, \dots$ to the tasks.
*   For the $i$-th task (0-indexed) with deadline $D_i$, we must perform it at time $t=i$.
*   Condition: We must complete the task *before* the deadline. So we need $i < D_i$.
*   If $i \ge D_i$ for any task, it's impossible to save everyone. Return -1.

### 4. Result
If the schedule is valid, the minimum number of barriers is simply the number of unique angles (tasks).

## Complexity
*   **Time:** $O(K \log K)$ for sorting deadlines. GCD and Map operations are efficient.
*   **Space:** $O(K)$ to store groups.
