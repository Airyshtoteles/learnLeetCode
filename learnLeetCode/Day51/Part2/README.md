# Day 51 Part 2: Tournament of Shadows – Optimal Skill Rotation

## Problem Description
You have `N` skills.
- `damage[i]`
- `cooldown[i]`
- `cast_time[i]`
Total time `T`.
Goal: Maximize damage.
Rules:
- Casting takes `cast_time[i]`.
- Cooldown starts after cast finishes.
- Cannot cast if on cooldown.

## Approach
This is a scheduling problem.
Since `N` is small (implied by "Tournament" and complexity of state), we can use DP.
State: `dp[t]` = max damage at time `t`.
However, we need to know cooldowns.
If `N` is small (e.g., <= 10), we can track `ready_time` for each skill.
State: `(current_time, ready_time_0, ready_time_1, ...)`
To reduce state space:
- `ready_time_i` is relevant only relative to `current_time`.
- `offset_i = max(0, ready_time_i - current_time)`.
- Max offset is `max(cooldown)`.
- If `max(cooldown)` is large, this is bad.
- But `T` is up to 200,000?
- If `T` is large, maybe `N` is very small?
- Or maybe `cooldown` is small?
- "Hint: job scheduling... unbounded knapsack".
- If `cooldown` is small, we can use the state.
- If `cooldown` is large, maybe we don't cast it often.

**Alternative Approach (DP on Time):**
`dp[t]` = max damage at time `t`.
To compute `dp[t]`, we consider the last skill cast.
Suppose last skill was `i`, finishing at `t`.
It started at `t - cast_time[i]`.
So `dp[t] = dp[t - cast_time[i]] + damage[i]`.
Constraint: `i` must be ready at `t - cast_time[i]`.
This requires knowing when `i` was used *before* that.
This implies we need to know the history of `i`.
This is the same problem as Part 4 of Day 50 (Spell Weaving).
In Day 50 Part 4, we used `dp[t] = max(dp[t-1], p[i] + dp[t-cd[i]])` as a heuristic/approximation.
Here, we have `cast_time` AND `cooldown`.
Total cycle time for skill `i` is `cast_time[i] + cooldown[i]`.
If we just spam skill `i`, we get `damage[i]` every `cast + cd`.
But we can interleave.
Given "Hard", maybe we need a better approach than the heuristic.
However, exact solution is NP-Hard (Job Shop Scheduling variant).
With `N` small, we can use `dp[mask]` where mask encodes cooldowns?
Or `dp[t]` with a small lookback?
Let's assume `N` is small (e.g. 3-5 skills) and implement a **Priority Queue Search (Dijkstra/A*)** on state `(time, ready_times)`.
Since we want max damage, we can use Dijkstra with negative weights (min negative damage).
State: `(ready_times_tuple)`. Value: `max_damage`.
We process states by time.
Actually, `time` is continuous.
Events happen when a skill finishes casting or a cooldown finishes.
But we only make decisions when a cast finishes.
So we jump from `t` to `t + cast_time[i]`.
State: `(current_time, ready_times)`.
We can normalize `ready_times` by subtracting `current_time`.
`state = (ready_offset_0, ready_offset_1, ...)`
`dp[state] = max_damage`.
But `current_time` matters because of `T`.
So `dp[time][state]`.
If `T` is large, this is too slow.
But maybe `state` converges?
Let's stick to the **DP Heuristic** from Day 50 but refined for `cast_time`.
`dp[t]` = max damage at time `t`.
`dp[t] = dp[t-1]` (idle).
For each skill `i`:
  `start_t = t - cast_time[i]`.
  If `start_t >= 0`:
    `prev_use = start_t - cooldown[i]`. (Actually `t - cast - cd`).
    `val = damage[i] + dp[start_t]`.
    Check validity?
    We assume `dp[start_t]` is compatible.
    This is the same approximation.
    Is there a better way?
    If `N` is small, we can use **Beam Search**.
    Keep top `K` states at each time step.
    State: `(damage, ready_times)`.
    At step `t`, generate next states.
    This is robust.

## Complexity
- **Time:** `O(T * N * BeamWidth)`.
- **Space:** `O(BeamWidth * N)`.
