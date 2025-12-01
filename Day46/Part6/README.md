# Part 6: The Voidstorm Spiral

## Problem Description

You are in an `N x M` arena.
*   **Start:** `(x0, y0)` with Health `H`.
*   **Voidstorm:** Every second, the arena boundary shrinks by 1 from all sides (Top, Bottom, Left, Right).
    *   At `t=0`, safe zone is `[0, N-1] x [0, M-1]`.
    *   At `t=1`, safe zone is `[1, N-2] x [1, M-2]`.
    *   ...
    *   At `t=k`, safe zone is `[k, N-1-k] x [k, M-1-k]`.
*   **Damage:** If you are outside the safe zone at the end of a second, you take `D` damage.
*   **Movement:** You can move 1 step in any of the 4 cardinal directions per second.
*   **Goal:** Maximize the time you stay alive (`H > 0`).

## Approach

The optimal strategy is to stay inside the safe zone as long as possible.
Since the safe zone shrinks concentrically towards the center of the grid, the safest place is the **center**.
*   Center of `N`: `(N-1)/2`.
*   Center of `M`: `(M-1)/2`.

**Logic:**
1.  **Move to Center:** Since we move at speed 1 and the boundary shrinks at speed 1, if we start inside the safe zone, we can always "outrun" or "keep up" with the shrinking boundary until the safe zone disappears completely.
    *   We simply move towards the center `(N/2, M/2)`.
2.  **Safe Duration:** The safe zone exists until `t` such that `t > N-1-t` or `t > M-1-t`.
    *   Max safe time `T_safe = (min(N, M) - 1) // 2`.
    *   Until `T_safe`, we take 0 damage (assuming we move optimally).
3.  **Damage Phase:** Once the safe zone vanishes (or becomes too small to exist), we take `D` damage every second.
    *   We can survive `(H - 1) // D` hits.
    *   Wait, if `H=10, D=10`, we take 1 hit and die? `H` becomes 0. "H > 0" required. So 0 hits?
    *   If `H=10, D=10`. Hit 1 -> H=0. Dead. Survival time = `T_safe`.
    *   If `H=11, D=10`. Hit 1 -> H=1. Alive. Hit 2 -> H=-9. Dead. Survival time = `T_safe + 1`.
    *   Formula: `ExtraTime = (H - 1) // D`.

**Algorithm:**
1.  Calculate `T_safe = (min(N, M) - 1) // 2`.
2.  Calculate `ExtraTime = (H - 1) // D`.
3.  `TotalTime = T_safe + ExtraTime`.
4.  (Optional) Simulate to verify.

**Simulation:**
*   Loop `t` from 1 upwards.
*   Update Safe Zone `[t, N-1-t]`.
*   Move Player towards center.
*   Check if Player in Safe Zone.
*   If not, `H -= D`.
*   If `H <= 0`, return `t-1`.

## Complexity
*   O(1) Formula.
*   O(N) Simulation.

