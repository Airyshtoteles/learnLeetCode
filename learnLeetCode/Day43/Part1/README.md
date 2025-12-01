# Dungeon Echo Propagation

Level: Hard

You are in an m x n grid.
- 0: Empty
- 1: Wall
- 2: Echo Source

Echo spreads every second to 4 neighbors.
Special rule: If echo hits a wall from a direction, it bounces back in the opposite direction in the next second with strength x2 (but only bounces once).
A cell is "heard" if any echo reaches it (any strength).

Task: Count total unique cells heard.

## Approach (BFS with State)
We simulate the wave propagation using BFS.
State: `(r, c, bounced)`
- `bounced`: boolean, true if this wave segment has already bounced off a wall.

Transitions:
1. Normal spread: From `(r,c)` to neighbor `(nr,nc)`.
   - If `(nr,nc)` is empty/source: add to queue.
   - If `(nr,nc)` is wall AND `!bounced`:
     - Reflect: The wave doesn't enter the wall but "bounces" back to `(r,c)` (or effectively stays/reverses) for the next step.
     - Actually, the problem says "bounced back in opposite direction". If moving Right hits wall, next step it moves Left from the wall surface?
     - Interpretation: If at `(r,c)` moving to `(nr,nc)` hits wall, the wave generates a new wavefront at `(r,c)` moving opposite direction in next step with `bounced=True`.
     - Since we only care *if* a cell is heard, strength doesn't strictly matter for reachability, only the bounce mechanic extends reach (or allows re-traversal).
     - However, "bounced once" limit means we track state.

We use a `visited[r][c][bounced]` set to avoid cycles/redundancy.
Count unique `(r,c)` in visited states where cell is not wall.

Complexity: O(m*n).
