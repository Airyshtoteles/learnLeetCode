# Minimum Walls to Break in a Rotating Maze

Level: Hard

You have an n x m grid with characters:
- '.' free
- '#' wall that toggles to free every 5 steps (becomes '.' at times in interval [5,9], [15,19], ...)
- 'R' rotating wall (always a wall in both phases)

After every 5 moves the phase flips; after 10 moves it returns to original. So pattern period = 10.
Breaking a wall costs 1; moving costs 0. Once broken a cell is considered free (we approximate by paying cost once when entering as a wall). Find minimum total wall-break cost from (0,0) to (n-1,m-1) moving 4-directionally.

## Model
State includes time modulo 10 to know whether '#' cells are free (phase 1) or walls (phase 0). A '#' cell is free only when phase = 1..5? We define phaseIndex = (time // 5) % 2: 0 original, 1 inverted. In inverted phase, '#' becomes '.'; 'R' stays a wall.

We perform Dijkstra / 0-1 BFS over (r,c,tmod10). Transition to neighbor increments time by 1. Cost to enter neighbor:
- 0 if cell is '.' OR (cell is '#' and phaseIndex==1)
- 1 otherwise (wall or 'R').

We keep minimal cost for (r,c,tmod10); answer minimal over time states at goal.

Complexity: O(n*m*10 log (n*m*10)).
