# The Locked Tiles (15-Puzzle)

Given a 4x4 board with tiles 1..15 and one blank (0), at each step you can swap 0 with one of its 4-neighbors. Find the minimum number of moves to reach the sorted goal state:

```
1  2  3  4
5  6  7  8
9  10 11 12
13 14 15 0
```

If the puzzle is unsolvable, return -1.

## Approach
- Serialize the board to a compact 16-character key using hexadecimal digits (0..F), where `0` is the blank and `1..F` are tiles 1..15.
- Use BFS from the initial key to the goal key. Each move swaps the blank with an adjacent tile.
- Before BFS, check solvability for 4x4 (even width):
  - Let inv = number of inversions in the flattened list excluding 0
  - Let r = row index of the blank counting from the bottom (1-based)
  - The puzzle is solvable iff `(inv + r) % 2 == 1` relative to the standard goal.

This guarantees we don't waste time BFSing impossible instances.

## Example
Input:

```
board = [
 [1,2,3,4],
 [5,6,7,8],
 [9,10,11,12],
 [13,15,14,0]
]
```

Output:

```
2
```

## Files
- `locked_tiles.py` — Python BFS with solvability check and a small demo
- `locked_tiles.cpp` — C++17 BFS implementation
