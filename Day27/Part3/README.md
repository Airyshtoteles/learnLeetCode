# Maze of Time

Grid n x m with cells that can be walls `#` or open `.` but some cells flip between wall and open every k seconds (k from `flip_interval`). Start `S`, end `E`. Each move (or waiting in place) takes 1 second. A move to a cell at time t+1 is valid only if source is open at t and destination is open at t+1. Find the minimum arrival time or -1.

- A cell with `flip_interval = 0` is static (never flips) and uses its initial character.
- A flipping cell toggles state every k seconds; period is 2k. At time t, if ⌊t/k⌋ is even it has its initial state, else toggled.

## Approach
BFS (or Dijkstra with unit weights) over states (x, y, t mod L):
- Let L be lcm of all non-zero periods (2k) to make the time dimension finite
- From a state, you can wait or move to 4 neighbors; check open/blocked at relevant times
- Mark visited by (x,y,t mod L)

## Files
- `maze_of_time.py` — Python BFS with waiting
- `maze_of_time.cpp` — C++17 BFS with waiting
