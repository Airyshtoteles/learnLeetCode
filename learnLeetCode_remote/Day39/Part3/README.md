# Optimal Dungeon Spells

Difficulty: Hard — Bitmask/State DP with Cooldowns

Rooms 1..n with HPs must be cleared in order. Spells `j=1..m` have `damage[j]`, `cooldown cd[j]`, and `mana cost cost[j]`. You start with `totalMana` and cooldowns carry across rooms. A cast takes 1 time unit, applies damage immediately, sets that spell's cooldown, and consumes mana. While waiting, cooldowns tick down.

Goal: Decide if the dungeon is clearable within `totalMana`, and if so, return the minimum total time.

## Approach (Greedy Ready-Highest-Damage + Event Simulation)
We simulate time with two operations:
- If any affordable spell is off cooldown, cast the one with largest damage (ties arbitrary). This is a 1 time unit action.
- Otherwise, wait until the soonest spell becomes available (advance time by the minimum remaining cooldown among affordable spells) and tick all cooldowns down by that amount.

We process rooms in order; cooldowns persist between rooms. If at any point no spells are affordable and all have positive cooldown (or all damages are zero), the dungeon is impossible.

This strategy is efficient in practice and optimal for single-target DPS with identical cast time under cooldown gating.

- Time: roughly `O(total casts + m * number of wait events)`
- Space: `O(m)`
