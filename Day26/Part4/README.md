# The Portal Maze

A 2D grid contains walls `#`, empty `.` cells, uppercase letters `A..Z` as portals, a start `S` and a target `T`.
Two identical letters form a portal pair: stepping into one teleports you to the other. Find the minimum number of steps from `S` to `T`.

- Moving to any of the 4 neighbors costs 1 step.
- If the destination cell is a letter, you immediately appear at its paired cell at no extra step.
- Avoid loops with standard BFS `visited` by coordinates.

## Approach
- Preprocess the positions of each letter.
- Standard BFS from `S`. From a cell, for each of 4 neighbors:
  - If wall `#`, skip
  - If `.`, `S`, or `T`, enqueue normally with `dist+1`
  - If letter `L`, enqueue its paired cell coordinate with `dist+1`

This avoids repeatedly bouncing between paired letters because we visit coordinates once at their shortest distance.

## Example
```
maze = [
 "S.A#",
 ".#A.",
 ".#..",
 "...T"
]
```
Output: `7`

## Files
- `portal_maze.py` — Python BFS with portals
- `portal_maze.cpp` — C++17 BFS with portals
