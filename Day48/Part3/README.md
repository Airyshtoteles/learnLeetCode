# Part 3: Dungeon Switchboard Optimization

## Problem Description

You are in a dungeon with `N` rooms connected by `M` edges.
Each room has a base **Lamp Color**: Red (0), Green (1), or Blue (2).

**Rules:**
1.  **Entry Condition:** You can only enter a room if its CURRENT color is **Green (1)**.
2.  **Switchboards:** Some edges contain "Magical Switchboards".
    *   If you traverse such an edge, it triggers a **Global Color Shift**.
    *   The shift rotates colors: Red -> Green -> Blue -> Red.
    *   Specifically, if the global shift count is `k`, the effective color of a room with base color `C` is `(C + k) % 3`.
3.  **Movement:** You start at `S`. You want to reach `T`.
    *   You can traverse any edge.
    *   If the edge has a switchboard, `k` increases by 1 (after you leave the source, but before you enter the destination? Or simultaneously?).
    *   Let's assume the check for the destination room happens *after* the shift (if any).

**Input:**
*   `N`: Number of rooms.
*   `Colors`: List of base colors for rooms 0 to N-1.
*   `Edges`: List of `[u, v, has_switch]`. Undirected.
*   `S`, `T`: Start and Target.

**Output:**
*   Minimum steps to reach `T`. Return `-1` if impossible.

**State:**
*   `(u, phase)` where `phase` is `k % 3`.
*   Current color of room `v` is `(Colors[v] + phase) % 3`.
*   Valid move `u -> v`:
    *   New phase `next_phase = (phase + 1) % 3` if edge has switch, else `phase`.
    *   Check: `(Colors[v] + next_phase) % 3 == 1` (Green).

### Example

**Input:**
```text
N = 3
Colors = [1, 0, 0] (Room 0: Green, Room 1: Red, Room 2: Red)
Edges = [
  [0, 1, 1], # Switchboard
  [1, 2, 0]  # Normal
]
S = 0, T = 2
```

**Logic:**
*   Start at 0. Base Color 1 (Green). Phase 0. Current Color (1+0)%3 = 1 (Green). OK.
*   Move 0 -> 1. Edge has switch.
    *   Next Phase = (0 + 1) % 3 = 1.
    *   Check Room 1: Base 0 (Red). Current (0 + 1)%3 = 1 (Green). OK.
    *   State: (1, 1). Steps: 1.
*   Move 1 -> 2. Edge normal.
    *   Next Phase = 1.
    *   Check Room 2: Base 0 (Red). Current (0 + 1)%3 = 1 (Green). OK.
    *   State: (2, 1). Steps: 2.
*   Reached T=2.

**Output:**
```text
2
```
