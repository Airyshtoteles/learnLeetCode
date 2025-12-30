# Day 55: The Chrono-Spatial Gauntlet

## Part 1: Time-Reversed Dungeon
**Problem:**
Navigate a dungeon with N rooms and M edges. Each room has a countdown timer `t[i]`. If you enter a room when `t[i] <= 0`, you die.
You have `K` "Rewinds". A Rewind reverses all edges in the dungeon for the *next step only*.
Find if it's possible to reach `Target` from `Start`.

**Input:**
- `n`: Rooms (0..n-1)
- `edges`: Directed edges `[u, v]`
- `t`: Array of timers
- `start`, `target`
- `k`: Max rewinds

**Output:** `true` or `false`.

## Part 2: Monster Orchestra
**Problem:**
Monsters play music in intervals `[start, end]` with power `p`.
You can destroy one continuous segment of length `L`. Any monster whose interval intersects this segment is silenced (power 0).
Maximize the total power of remaining monsters.

**Input:**
- `intervals`: `[[s, e, p], ...]`
- `L`: Length of destruction segment

**Output:** Max remaining power.

## Part 3: Dual-World Chessboard
**Problem:**
Grid NxN with two worlds: Light (0) and Dark (1).
- Light Move: Standard Knight (L-shape).
- Dark Move: Double Knight Jump (2 consecutive jumps as one move).
- Portals: Some cells allow switching worlds (Cost 1).
- Hazards: Some cells are blocked in specific worlds.
Find min steps from `(sx, sy, Light)` to `(tx, ty, Dark)`.

**Output:** Min steps or -1.

## Part 4: Gravity-Shift Arena
**Problem:**
Grid with Start `S`, Target `T`, Walls `#`.
Each turn:
1. Choose Gravity (Up, Down, Left, Right).
2. Fall until blocked.
3. Arena rotates 90 degrees Clockwise.
Find min turns to reach `T`.

**Output:** Min turns or -1.

## Part 5: Clone Warfield
**Problem:**
Enemies at positions `E[]` on a line. Player at `S`.
Player moves (cost 1/step).
Player can spawn Clones:
- Clone lives `L` steps.
- Clone moves 1 step/turn.
- Clone kills 1 enemy then vanishes.
Minimize total cost (Player steps + Clone steps) to kill all enemies.

**Output:** Min cost.
