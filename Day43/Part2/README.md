# Crumbling Island Survival

Level: Hard

Grid n x n. `t[i][j]` is the time when cell `(i,j)` collapses.
Start `(0,0)`, Target `(n-1,n-1)`.
Move 4 directions, 1 sec per step.
Constraint: You can only be at `(i,j)` at time `arrival_time` if `arrival_time < t[i][j]`.
Find minimum time to reach target.

## Approach (Dijkstra)
Standard shortest path on grid.
Nodes: `(r, c)`
Edge weight: 1
Constraint check: `current_time + 1 < t[next_r][next_c]`.

Wait, is it possible to wait? "Player tidak boleh menginjak sel pada detik di mana sel tersebut runtuh atau setelahnya."
Usually in such problems, waiting doesn't help because the deadline is fixed per cell. Moving earlier is always better or equal.
So standard Dijkstra works.

State: `dist[r][c]` = min time to reach `(r,c)`.
Priority Queue stores `(time, r, c)`.

Initial: `pq = [(0, 0, 0)]` if `0 < t[0][0]`. Else impossible.

Complexity: O(n^2 log n).
