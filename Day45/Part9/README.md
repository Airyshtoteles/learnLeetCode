# Day 45 Part 9: K-Player Asymmetric Battle Royale Simulation

## Problem Description

$K$ players fight in an arena.
*   **Attributes:**
    *   `HP`: Health Points.
    *   `Attack`: Damage dealt.
    *   `Range`: Attack range.
    *   `Speed`: Movement speed.
    *   `Pos`: $(x, y)$ coordinates.
*   **Simulation Step (1 second):**
    1.  **Move:** All players move towards the nearest *living* opponent.
        *   Distance moved = `Speed`.
        *   If distance to target < `Speed`, move to target (collision?).
        *   Let's assume they stop at range or collision.
    2.  **Attack:**
        *   Players attack if a target is in `Range`.
        *   **Order:** The order of attacks is determined by a "Seed Cycle".
        *   If A kills B, B is removed immediately and cannot attack later in the same turn.
*   **RNG / Seed Cycle:**
    *   We are given a cycle of seeds (or permutations).
    *   At time $t$, use `Cycle[t % Len]`.
*   **Goal:** Determine the survivor(s).
*   **Output:** The ID of the survivor. (If multiple, maybe the one with highest HP?).

## Algorithm: Discrete Event Simulation

Since the "Seed Cycle" is known, the simulation is deterministic.
We simply run the simulation step-by-step until 0 or 1 player remains.

### Movement Logic
*   For each player $P$:
    *   Find nearest enemy $E$.
    *   Vector $V = E.pos - P.pos$.
    *   Normalize $V$, scale by $P.speed$.
    *   Update $P.pos$.

### Attack Logic
*   Get permutation for current turn from Cycle.
*   For each attacker $A$ in permutation:
    *   If $A$ is dead, skip.
    *   Find nearest enemy $E$ in $A.range$.
    *   If multiple, pick one (e.g., lowest HP or ID).
    *   $E.HP -= A.damage$.
    *   If $E.HP \le 0$, mark $E$ as dead.

### Complexity
*   $K$ is small (e.g., 10).
*   Simulation runs until end.
*   $O(T \times K^2)$ per step.

## Implementation Details
*   Input: List of players, Seed Cycle (list of permutations).
*   Output: Survivor ID.

```python
players = [
    {'id': 0, 'hp': 100, 'atk': 10, 'rng': 2, 'spd': 1, 'pos': (0,0)},
    # ...
]
cycle = [
    [0, 1, 2], # Turn 0 order
    [2, 1, 0], # Turn 1 order
    # ...
]
```
