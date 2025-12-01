# Part 2: Summoning Stones Tower Defense

## Problem Description

You have a linear path of length `N`.
Enemies appear at position `0` at specific times `enemies[i]` and move right at `1` unit/sec.
You have `K` Summoning Stones (Towers).
*   **Placement:** Each stone can be placed at any integer coordinate `0 <= p <= N`.
*   **Range:** A stone at `p` can attack enemies in `[p-r, p+r]`.
*   **Attack:** Instantly kills one enemy.
*   **Cooldown:** 3 seconds.

**Goal:**
Find the optimal placement of `K` stones to maximize the total number of killed enemies.

## Approach

This problem combines **Combinatorial Optimization** (choosing tower positions) with **Greedy Simulation** (scheduling attacks).

### 1. Tower Placement (Combinatorics)
Since the path length `N` and number of towers `K` are relatively small for this challenge (e.g., `N=20, K=3`), we can iterate through all possible combinations of tower positions.
*   Total combinations: `C(N+1, K)`.
*   For each combination, we run a simulation to calculate the max kills.

### 2. Attack Simulation (Greedy with Earliest Deadline First)
For a fixed set of tower positions, we need to decide which enemy each tower should attack at any given time.
*   **Time Discretization:** We simulate second by second.
*   **Candidate Targets:** At time `t`, identify all (Tower, Enemy) pairs where the enemy is in range and the tower is ready (off cooldown).
*   **Greedy Strategy:** Among all valid pairs, prioritize killing the enemy that is **closest to leaving the range** (Earliest Deadline First).
    *   If an enemy is about to exit the range of a tower, we should kill it now.
    *   If multiple towers can kill the same "urgent" enemy, pick the tower that has the *least* utility for other urgent enemies (or just pick arbitrarily for simplicity).

### Algorithm
1.  Generate all combinations of `K` positions from `0` to `N`.
2.  For each combination:
    *   Initialize `kills = 0`.
    *   Initialize `tower_ready_time` for each tower to `0`.
    *   Track `alive_enemies`.
    *   Loop `t` from `0` to `MaxTime`:
        *   Identify all valid attacks: `(Enemy, Tower)` where `dist(Enemy, Tower) <= R` and `Tower.ready <= t`.
        *   Sort attacks by `Enemy.ExitTime` (when they leave the tower's range).
        *   Execute attacks:
            *   If `Enemy` is alive and `Tower` is ready:
                *   Kill Enemy.
                *   Set `Tower.ready = t + 3`.
                *   Increment `kills`.
    *   Update `MaxKills`.
3.  Return `MaxKills`.

## Complexity
*   **Outer Loop:** `O(N^K)` combinations.
*   **Inner Simulation:** `O(T * K * E)` where `T` is duration, `E` is number of enemies.
*   Feasible for small `N, K`.

