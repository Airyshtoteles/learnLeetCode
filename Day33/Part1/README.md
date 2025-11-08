# Matrix Shadow Expansion

Difficulty: Hard

You are given an n x n integer matrix `grid`. Each cell `(i, j)` casts a shadow of length `grid[i][j]` to the right and down (including itself). If a cell is covered by any shadow, it’s considered “darkened”. Return the total number of unique darkened cells after all shadows have been cast.

Example
```
Input: grid = [[1,2],
               [3,1]]
Output: 6
```

## Approach
We treat each cell as starting two segments:
- Horizontal segment on row `i`: from column `j` to `min(n-1, j + grid[i][j] - 1)`
- Vertical segment on column `j`: from row `i` to `min(n-1, i + grid[i][j] - 1)`

We need the size of the union of all covered cells by these segments. We can compute it in `O(n^2)` time and `O(1)` extra space by scanning:

1) Row scan (left to right). Maintain a counter `rem` = remaining horizontal coverage from any started segment so far. At column `j`, if `rem > 0`, the cell is horizontally covered. Then set `rem = max(rem-1, grid[i][j])`. We count horizontally covered cells and mark them in-place by adding a large constant `BASE` to `grid[i][j]` (so we can later detect horizontal coverage without extra memory). We always read the original value as `grid[i][j] % BASE`.

2) Column scan (top to bottom). Similarly maintain `rem` for vertical coverage using original values (via modulo). Count vertically covered cells; if a cell is both horizontally covered (detected as `grid[i][j] >= BASE`) and vertically covered, count it in the intersection.

Answer = (horizontal count) + (vertical count) - (intersection count).

This mutates the grid during computation, but we only add multiples of `BASE`, so original values are retrievable via modulo if needed.

## Complexity
- Time: `O(n^2)`
- Extra Space: `O(1)` (in-place marking)
