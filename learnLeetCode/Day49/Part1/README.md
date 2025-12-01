# Part 1: Game of Dissonant Mirrors

## Problem Description

You are navigating an `N x M` grid containing `0`s and `1`s.
*   Start: `(0, 0)`.
*   Target: `(N-1, M-1)`.

**Rules:**
1.  You can move Up, Down, Left, Right.
2.  **Mirror Effect:**
    *   If you move to a cell with value `0`: The grid state remains unchanged.
    *   If you move to a cell with value `1`: The **entire grid** flips states (`0` becomes `1`, `1` becomes `0`).
    *   This flip happens *after* you land on the cell (or effectively *as* you enter).
    *   The value of the cell you *just entered* (which was `1`) becomes `0` after the flip.
    *   The value of the cell you *left* also flips.

**Goal:** Find the minimum steps to reach `(N-1, M-1)`.

**State:**
*   `(r, c, grid_state)`
*   `grid_state`: `0` (Original), `1` (Inverted).
*   Value of cell `(r, c)` at `grid_state`: `Original[r][c] ^ grid_state`.

**Transitions:**
*   From `(r, c, state)`, try moving to `(nr, nc)`.
*   Let `val = Original[nr][nc] ^ state`.
*   If `val == 0`: New state is `(nr, nc, state)`. Cost +1.
*   If `val == 1`: New state is `(nr, nc, 1 - state)`. Cost +1.

### Example

**Input:**
```text
Grid = [
  [0, 1],
  [1, 0]
]
```

**Path:**
1.  Start `(0,0)`. Value 0. State 0.
2.  Move to `(0,1)`. Original `1`. `1^0 = 1`.
    *   We land on a `1`. Grid flips. State becomes `1`.
    *   Current pos `(0,1)`.
3.  Move to `(1,1)`. Original `0`. `0^1 = 1`.
    *   We land on a `1` (because grid is inverted). Grid flips. State becomes `0`.
    *   Current pos `(1,1)`. Target reached.
    *   Total steps: 2.

**Output:**
```text
2
```
