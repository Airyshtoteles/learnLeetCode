# Day 52 Part 4: Chrono Arena Turn Scheduler

## Problem Description
In the Chrono Arena, combat is governed by an Active Time Battle (ATB) system.
You control a hero with a specific **Speed** $S$.
The Action Gauge requires 100 units to fill.
Time to fill gauge = $100 / S$.

When the gauge is full, the hero can choose to use one of $N$ skills.
Each skill $i$ has:
- `Damage`: $D_i$
- `Cast Time`: $C_i$ (Time spent executing the skill. Gauge does not fill during this).
- `Cooldown`: $CD_i$ (Skill cannot be used again for this duration).
- `CP Cost/Gain`: $CP_i$ (Positive adds CP, Negative requires and consumes CP).

**Rules:**
1. **Cycle**:
   - Wait for Gauge to fill: $T_{fill} = 100/S$.
   - Choose a valid skill $i$ (Not on cooldown, sufficient CP).
   - Execute skill: Takes $C_i$ time.
   - Total time elapsed in step: $T_{fill} + C_i$.
   - Update CP: $CP = \min(5, \max(0, CP + CP_i))$.
   - Update Cooldowns: All skills recover by $T_{fill} + C_i$.
   - Skill $i$ goes on cooldown $CD_i$.
2. **Constraints**:
   - Max CP is 5. Initial CP is 0.
   - Total Time Limit $T_{limit}$.
   - You cannot use a skill if you don't have enough CP.
   - You cannot use a skill if it is on cooldown.

**Goal:**
- Maximize total damage within $T_{limit}$.

## Input Format
- `S`: Speed (float).
- `T_limit`: Total time (float).
- `skills`: List of tuples `(name, damage, cast_time, cooldown, cp_change)`.

## Constraints
- $N \le 10$
- $T_{limit} \le 1000$
- $S > 0$

## Strategy
This is a state-space search problem.
**State**: $(current\_time, CP, cooldowns)$
- $current\_time$: Accumulated time.
- $CP$: Current Combo Points (0-5).
- $cooldowns$: Tuple of "time when ready" for each skill.

Since we want to maximize damage, and the state space can be large (continuous time), we can use **Beam Search** or **DP with discretization**.
Given $N$ is small and we make discrete choices (which skill to use next), Beam Search is suitable.
We only care about the sequence of skills.
However, waiting for cooldowns is NOT an option in this model (you act immediately when gauge is full). If the desired skill is on cooldown, you must pick another or wait?
Usually in ATB, if you wait, the enemy acts. Here, it's a "Turn Scheduler" optimization.
Assumption: You **must** act when the gauge is full. You can only pick available skills. If no skill is available (e.g. all on CD or no CP), you must "Skip" (Wait)?
Let's add a "Wait/Skip" action: Takes 0 cast time, 0 damage, 0 CP change. Just resets gauge? No, that would be infinite loop.
Let's say "Skip" takes a small penalty time (e.g. 1.0s) to "pass" turn.
Or better: You can only choose valid skills. If none valid, you lose the turn (time advances by fill time, but no action taken? No, gauge is full).
Let's assume there is always a "Basic Attack" with 0 CD and 0 CP cost.

**Algorithm**:
- Beam Search.
- Keep top $K$ states at each "Turn" (depth).
- Or keep top $K$ states sorted by (Damage / Time)?
- Since time varies, we should order states by `current_time`.
- Priority Queue: `(current_time, -damage, CP, cooldowns)`.
- Expand state with min time.

## Complexity
- Branching factor $N$.
- Depth $\approx T_{limit} / (100/S)$.
- With Beam Width $W=100$, feasible.

