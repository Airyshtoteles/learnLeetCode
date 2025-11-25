# Part 5: Forbidden Hex Arena

## Problem Description

You are a gladiator in the "Forbidden Hex Arena", a magical battleground laid out on a **Hexagonal Grid**.
The grid uses **Cube Coordinates** `(x, y, z)` where `x + y + z = 0`.

You start at the center `(0, 0, 0)`.
You must reach the **Exit Portal** at `(tx, ty, tz)`.

**Movement Options:**
1.  **Walk:** Move to an adjacent hex. Cost: **1**.
    *   Neighbors are: `(+1,-1,0), (+1,0,-1), (0,+1,-1), (-1,+1,0), (-1,0,+1), (0,-1,+1)`.
2.  **Blink:** Dash in a straight line along any of the 6 axes to any valid hex. Cost: **2**.
    *   You cannot blink through or land on "Forbidden" (blocked) hexes.
    *   The path must be clear.
3.  **Rune Teleport:** If you are standing on a "Rune" hex, you can instantly teleport to **any other** Rune hex. Cost: **1**.

**Input:**
1.  `Target`: `[tx, ty, tz]`.
2.  `Blocked`: List of `[x, y, z]` coordinates that are obstacles.
3.  `Runes`: List of `[x, y, z]` coordinates that act as teleporters.

**Output:**
*   Minimum cost to reach the target. Return `-1` if unreachable.

**Constraints:**
*   Coordinates are within `[-50, 50]`.
*   The arena is bounded by `max(|x|, |y|, |z|) <= 50`.

### Example

**Input:**
```text
Target = [0, -2, 2]
Blocked = [[0, -1, 1]] (Blocks the direct path south)
Runes = [[1, -1, 0], [0, -2, 2]] (Rune at neighbor and at target)
```

**Path:**
1.  Start (0,0,0).
2.  Walk to (1, -1, 0). Cost 1. (This is a Rune).
3.  Teleport to (0, -2, 2). Cost 1.
4.  Total Cost: 2.

**Alternative Path (Blink):**
*   Can we blink from (0,0,0) to (0,-2,2)?
*   Line: (0,0,0) -> (0,-1,1) -> (0,-2,2).
*   (0,-1,1) is Blocked. Cannot blink through it.

**Output:**
```text
2
```
