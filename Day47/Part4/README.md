# Part 4: Chrono Arena Turn Scheduler

## Problem Description

In the Chrono Arena, you face a sequence of incoming attacks from a time-manipulating boss. You have a "Chrono Shield" that can block all damage for a short duration, but it has a cooldown.

You are given a list of `N` attacks. Each attack occurs at a specific `time` and deals a specific amount of `damage`.
You have a shield with:
*   **Duration (`D`):** Once activated at time `T`, it blocks ALL attacks occurring in the interval `[T, T + D]`.
*   **Cooldown (`C`):** After the shield expires at `T + D`, it cannot be reactivated until `T + D + C`.

You can choose to activate the shield at the exact moment of any incoming attack (to block it and potentially others). If you don't shield, you take the damage.

Find the **minimum total damage** you must take.

### Input Format
1.  `N`: Number of attacks.
2.  `D`: Shield Duration.
3.  `C`: Shield Cooldown.
4.  `Attacks`: List of pairs `[time, damage]`. Sorted by time.

### Output Format
*   Integer representing minimum damage taken.

### Example

**Input:**
```text
N = 5
D = 3 (Shield lasts 3 seconds)
C = 2 (Cooldown 2 seconds)
Attacks = [
  [1, 10],
  [2, 20],
  [4, 10],
  [6, 50],
  [8, 5]
]
```

**Logic:**
*   **Option 1:** Take hit 1 (Time 1). Damage 10. Remaining: [2, 4, 6, 8].
*   **Option 2:** Shield at Time 1.
    *   Active: [1, 1+3] = [1, 4].
    *   Blocks: Attack at 1 (10), Attack at 2 (20), Attack at 4 (10). (Since 4 <= 4).
    *   Shield Ends: 4.
    *   Cooldown Ends: 4 + 2 = 6.
    *   Next available shield time: >= 6.
    *   Attacks in gap (4 < t < 6): None.
    *   Next decision: Attack at 6.
    *   Subproblem: Start from Attack at 6.
        *   If we shield at 6: Blocks [6, 9]. Blocks 6 (50) and 8 (5). Total taken = 0.
    *   Total for this path: 0 (blocked 1,2,4) + 0 (blocked 6,8) = 0?
    *   Wait, can we shield at 6? Yes, cooldown ended at 6.
    *   So total damage = 0.

**Let's check another path:**
*   Shield at 2.
    *   Take hit 1 (10).
    *   Shield at 2. Blocks [2, 5]. Blocks 2 (20), 4 (10).
    *   Cooldown ends 2+3+2 = 7.
    *   Attack at 6 (50) is in cooldown period! Must take 50.
    *   Next decision: Attack at 8.
    *   Total: 10 + 50 + ...

**Output:**
```text
0
```
(Wait, is 0 realistic? Yes, if the shield covers everything perfectly. Let's assume the example allows 0).

**Another Example:**
Attacks: `[[1, 10], [3, 10], [5, 10]]`, D=1, C=2.
*   Shield at 1. Blocks [1, 2]. Blocks 1.
*   Cooldown ends 1+1+2 = 4.
*   Attack at 3 is in cooldown. Take 10.
*   Attack at 5 is available. Shield at 5. Blocks 5.
*   Total: 10.

### Constraints
*   `1 <= N <= 10^5`
*   `1 <= D, C <= 10^9`
*   `1 <= time, damage <= 10^9`
