# Day 50 Part 3: The Shifting Maze of Echoes

## Problem Description
You are in an `m x n` grid maze.
Walls (`#`) shift to the right every step.
- If `grid[r][c]` is `#`, then at next step `grid[r][c+1]` becomes `#`.
- Effectively, `IsWall(r, c, t)` is true if `OriginalGrid[r][c-t]` was `#`.
- If `c-t < 0`, it's empty (walls come from initial configuration, nothing enters from left).

You can perform `k` **Echo Shifts**: permanently flip a cell (`#` <-> `.`).
However, since walls are dynamic, "flipping a cell" is ambiguous.
Interpretation: We can traverse a wall cell by paying 1 flip cost.
Goal: Reach `(m-1, n-1)` from `(0, 0)`.

## Approach
We model this as a shortest path problem on a dynamic grid.
State: `(r, c)`.
We want to find a path with minimum flips.
Since walls move right, the condition for `(r, c)` being a wall at time `t` is `OriginalGrid[r][c-t] == '#'`.
We can wait at a cell. Waiting increases `t`.
Since `c-t` decreases as `t` increases, eventually `c-t < 0` and the cell becomes safe forever.
Thus, we can always wait until a cell becomes safe (cost 0), unless we are forced to move into a wall or die waiting.
But the problem says "If cell is '#', next step right is '#'". It doesn't say the current cell becomes '.'.
However, "If cell is '.', it stays '.'".
This implies walls **spread** (copy) to the right.
If walls spread, the row fills up.
So `IsWall(r, c, t)` is true if `any(OriginalGrid[r][0...c])` is `#`?
Wait, "If cell is '#', next step right is '#'".
This means `New[c+1] = Old[c+1] OR Old[c]`.
So yes, walls spread to the right.
Eventually, if there is a wall at `(r, 0)`, the whole row `r` becomes blocked.
We need to cross these walls.
Cost to enter `(r, c)` is 1 if it is currently a wall.
Since walls only grow, if it's a wall now, it stays a wall.
So `IsWall(r, c)` is effectively static based on the "Spread" logic?
Actually, at time `t`, the wall front has advanced `t` steps.
`IsWall(r, c, t)` is true if `OriginalGrid[r][c]` is `#` OR `OriginalGrid[r][c-1]` is `#` (if `t>=1`) ... OR `OriginalGrid[r][c-t]` is `#`.
Basically, `IsWall(r, c, t)` is true if there is any wall in `OriginalGrid[r][max(0, c-t) ... c]`.
As `t` increases, the range `[max(0, c-t), c]` grows to the left.
Eventually it covers `[0, c]`.
So waiting makes it **worse** (more likely to be a wall).
Therefore, we should move as fast as possible?
Or maybe we use flips to punch through.
We use **Dijkstra's Algorithm**.
State: `(r, c)`.
Distance: `min_flips`.
Priority Queue: `(flips, time, r, c)`.
We prioritize min flips. Tie-break with min time (since waiting is bad).
Actually, if we reach `(r, c)` with `f` flips at time `t1` vs `t2` ($t1 < t2$):
At `t1`, the wall range is `[c-t1, c]`.
At `t2`, the wall range is `[c-t2, c]`.
The range at `t2` is a superset of `t1`.
So `IsWall` at `t2` is more likely true.
So earlier is always better.
Thus, standard Dijkstra works. `dist[r][c]` stores `(flips, time)`.
We compare pairs. `(f1, t1) < (f2, t2)` if `f1 < f2` or `f1 == f2` and `t1 < t2`.

## Complexity
- **Time:** `O(M * N * log(MN))`.
- **Space:** `O(M * N)`.
