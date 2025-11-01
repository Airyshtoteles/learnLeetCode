# The Mirror Dungeon

You are on an n x n grid. Each cell is empty `.`, a wall `#`, or a mirror `/` or `\`.
You start at (0, 0) facing right and want to reach (n-1, n-1). When you enter a cell
with a mirror, your direction changes according to the mirror. You may flip a mirror
(`/` ↔ `\`) at cost 1. Find the minimum mirrors to flip to be able to reach the goal.

- Start: (0,0), initial direction: right
- Goal: reach (n-1, n-1) in any facing direction
- Move: step forward to adjacent cell in current direction; if that cell is a mirror, your
  facing direction immediately reflects; if you flip it first, it reflects as the other type
- Walls `#` are impassable

## Approach
Use Dijkstra (or 0-1 BFS) over states (x, y, dir) with edge costs in {0,1}:
- From (x,y,dir), attempt to step to (nx,ny) = (x+dx[dir], y+dy[dir]) if in bounds and not `#`.
- Let c be the cell at (nx,ny):
  - If c is `.`, new state is (nx,ny,dir) with cost +0
  - If c is `/`, two options:
    - keep `/`: direction reflects by `/` with +0
    - flip to `\`: direction reflects by `\` with +1
  - If c is `\`, likewise: keep `\` (+0) or flip to `/` (+1)
- The answer is the minimal distance among any direction at (n-1,n-1).

Time complexity: O(n^2 * 4 * log(n^2)) in practice, since each state has ≤ 2 outgoing edges.

## Example
Input:

```
n = 4
grid = [
  ".#..",
  "..\\.",
  "#...",
  "...#"
]
```

Output:

```
2
```

## Files
- `mirror_dungeon.py` — Python implementation with a small demo
- `mirror_dungeon.cpp` — C++17 implementation with the same logic
