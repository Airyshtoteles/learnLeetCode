# Part 4: Arcane Cooldown Optimizer

## Problem Description

You have a set of `N` skills.
Each skill `i` has:
*   `castTime[i]`: Time taken to cast the skill (seconds).
*   `damage[i]`: Damage dealt at the end of the cast.
*   `cooldown[i]`: Time required to recharge after the cast finishes.

**Mechanics:**
*   You can only cast one skill at a time.
*   Once a skill starts casting, you are busy for `castTime[i]`.
*   After `castTime[i]`, the damage is dealt, and the skill enters cooldown for `cooldown[i]`.
*   The skill becomes available again at `startTime + castTime[i] + cooldown[i]`.
*   You want to maximize total damage within a total duration `T`.

**Goal:**
Find the maximum damage possible in `T` seconds.

## Approach

This is a scheduling problem. Given the constraints (`N <= 100`, `T <= 10^5`) and the nature of the problem ("Greedy Hard"), a pure DP approach is difficult due to the need to track the cooldown state of all `N` skills.

However, we can employ a **Greedy Strategy with Simulation**.
The intuition is that we should always prioritize the skill that gives the best "bang for the buck" (Damage per second of Cast Time) among the currently available skills.

**Greedy Metric:** `DPS = Damage / CastTime`.
*   We want to spend our "busy time" casting the most efficient spells.
*   If a high-efficiency spell is on cooldown, we look for the next best available one.
*   If no spells are available (all on cooldown), we wait (advance time to the earliest ready time).

**Algorithm:**
1.  Sort skills by `DPS` descending.
2.  Initialize `currentTime = 0`.
3.  Initialize `readyTime[i] = 0` for all skills.
4.  Loop while `currentTime < T`:
    *   Find the best skill `i` such that `readyTime[i] <= currentTime`.
        *   "Best" means highest DPS.
        *   If multiple have same DPS, pick highest Damage.
    *   If a skill is found:
        *   Check if `currentTime + castTime[i] <= T`.
        *   If yes:
            *   Cast it.
            *   `totalDamage += damage[i]`.
            *   `currentTime += castTime[i]`.
            *   `readyTime[i] = currentTime + cooldown[i]`.
        *   If no (not enough time left):
            *   We can't cast this. Try next best?
            *   Actually, if we can't cast the best, we might fit a smaller one.
            *   So we iterate down the list.
    *   If no skill is ready:
        *   Advance `currentTime` to the minimum `readyTime` of all skills.
        *   If `min(readyTime) > T`, break.

**Refinement:**
Is `Damage / CastTime` strictly optimal?
Consider:
*   Skill A: 100 Dmg, 10s Cast, 0 Cool. (10 DPS)
*   Skill B: 10 Dmg, 1s Cast, 0 Cool. (10 DPS)
*   Both are equal.
Consider:
*   Skill A: 100 Dmg, 10s Cast, 100s Cool. (10 DPS)
*   Skill B: 9 Dmg, 1s Cast, 0 Cool. (9 DPS)
*   We should cast A whenever possible, then fill with B.
*   Our greedy logic does exactly this: A has higher DPS, so we pick it if ready. If A is on cooldown, we pick B.

This strategy effectively maximizes the utilization of the highest-value skills.

## Complexity
*   Simulation steps: Roughly `T / min(CastTime)`.
*   Per step: Scan `N` skills.
*   Total: `O(N * T)`. With `N=100, T=10^5`, operations ~ `10^7`, which fits within 1-2 seconds.

