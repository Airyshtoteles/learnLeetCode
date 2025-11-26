# Part 2: Time-Loop Survivors Arena

## Problem Description

You are in an `N x N` arena. Enemies spawn at specific times.
You have 3 skills, each with a cooldown. You can use at most **1 skill per second**.

**Skills:**
1.  **Slash:** Deals `d1` damage to a single target. Cooldown `c1`.
2.  **Pierce:** Deals `d2` damage to a target and one enemy directly behind it. Cooldown `c2`.
3.  **Shockwave:** Deals `d3` damage to ALL enemies within Manhattan Radius `R`. Cooldown `c3`.

**Input:**
*   `T`: Total duration (seconds).
*   `Skills`: `[d1, c1, d2, c2, d3, c3, R]`.
*   `Enemies`: List of `[spawn_time, x, y, hp]`.

**Goal:** Maximize the number of kills by time `T`.

**Simplification for Implementation:**
*   We will assume a simplified targeting logic for the DP state.
*   At each second `t`, we can choose:
    *   **Wait:** Cooldowns decrease.
    *   **Slash:** If `cd1 == 0`. We greedily target the enemy with lowest HP that we can kill, or just highest HP if we can't kill any? To maximize kills, we should kill low HP ones.
    *   **Pierce:** If `cd2 == 0`. We assume optimal targeting (hits 2 best targets).
    *   **Shockwave:** If `cd3 == 0`. Hits all in radius.

**DP State:**
*   `dp[t][cd1][cd2][cd3]` = Max Kills.
*   However, tracking exact HP of all enemies in the state is impossible ($2^N$).
*   **Constraint:** If $N$ (enemies) is small (e.g., <= 15), we can use bitmask for alive enemies.
*   **Revised State:** `dp[t][mask][cd1][cd2][cd3]`.
    *   `t`: 0 to T.
    *   `mask`: Bitmask of alive enemies.
    *   `cd`: Cooldowns.
*   Since `cd` can be up to `T`, and `T` might be large, this is hard.
*   But `cd` only matters up to the max cooldown of the skill.
*   Let's assume `N` is small (e.g., 10) and `T` is small (e.g., 20).

### Example

**Input:**
```text
T = 5
Skills = [10, 2, 15, 3, 5, 4, 2] (Slash 10/2s, Pierce 15/3s, Shock 5/4s/R2)
Enemies = [
  [0, 0, 0, 20],  # E0: Spawn t=0, HP 20
  [1, 0, 1, 10]   # E1: Spawn t=1, HP 10
]
```

**Logic:**
*   t=0: E0 active (20 HP).
    *   Slash E0: HP->10. CD1=2.
*   t=1: E0 (10), E1 (10) active.
    *   CD1=1. Can't Slash.
    *   Shockwave? Dmg 5. E0->5, E1->5. CD3=4.
*   t=2: E0 (5), E1 (5).
    *   CD1=0. Slash E0? HP->-5 (Dead). Kill+1. CD1=2.
*   t=3: E1 (5).
    *   CD1=1.
    *   Pierce? Dmg 15. E1->-10 (Dead). Kill+1.
*   Total Kills: 2.

**Output:**
```text
2
```
