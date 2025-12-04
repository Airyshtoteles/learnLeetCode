# Day 57: Advanced Algorithmic Challenges

## 1. Spiral Kingdom Conquest
**Problem:**
Conquer an $N \times N$ grid starting from the center in a spiral pattern (CW or CCW).
- Damage taken: `max(0, power - shield)`.
- Shield gain: `floor(power / 3)`.
- Find minimum damage between CW and CCW traversals.

**Constraints:**
- $N \le 1500$
- $power \le 10^9$

## 2. Chrono-Shift Board Game
**Problem:**
Minimize damage from enemies on a 1D board.
- Damage occurs if `attackTime[i] == 0` when player is at `i`.
- Player moves 1 step per unit time.
- Ability: Choose subarray $[l, r]$, reduce `attackTime` by $k = r - l + 1$.
- Minimize count of `i` where `attackTime'[i] == i`.

**Constraints:**
- $N \le 2 \cdot 10^5$

## 3. Dual-Realm Maze Shifter
**Problem:**
Navigate a maze with two realms 'A' and 'B'.
- Move adjacent: Cost 1.
- Switch realm: Cost 2 (uses 1 shift token).
- Max $K$ shifts.
- Find min cost to target.

**Constraints:**
- $N, M \le 300$
- $K \le 50$
