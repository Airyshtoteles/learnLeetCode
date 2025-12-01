# Part 3: Celestial Platform Shifter

## Problem Description

You are navigating a floating celestial temple represented by an `N x N` grid of platforms. Each platform at coordinates `(r, c)` has a specific height `H[r][c]`.

You start at `(0, 0)` and must reach the "Sanctum" at `(N-1, N-1)`.

**Movement Rules:**
1.  You can move Up, Down, Left, or Right to an adjacent platform.
2.  The base cost of a move is **1 second**.
3.  **Jump Limit:** You can naturally jump up to a height difference of `K`.
    *   If `H[next] <= H[current] + K`, the move costs only the base **1 second**.
    *   If `H[next] > H[current] + K`, you must use "Celestial Shift" magic to bridge the gap. The magic cost is added to the time.
    *   **Magic Cost:** `H[next] - (H[current] + K)`.
    *   Total Cost for move = `1 + max(0, H[next] - (H[current] + K))`.
4.  Dropping down (moving to a lower height) is always free of magic cost (just 1 second), as `H[next] < H[current]`.

Find the **minimum total cost** to reach `(N-1, N-1)`.

### Input Format
1.  `N`: Grid size (Integer).
2.  `K`: Max natural jump height (Integer).
3.  `Grid`: `N x N` matrix of integers representing heights.

### Output Format
*   Integer representing the minimum cost.

### Example

**Input:**
```text
N = 3
K = 2
Grid = [
  [0, 5, 10],
  [2, 3, 8],
  [10, 1, 9]
]
```

**Path:**
1.  (0,0)[H=0] -> (1,0)[H=2]. Diff=2. <= K(2). Cost = 1. Total = 1.
2.  (1,0)[H=2] -> (1,1)[H=3]. Diff=1. <= K(2). Cost = 1. Total = 2.
3.  (1,1)[H=3] -> (1,2)[H=8]. Diff=5. > K(2). Penalty = 8 - (3+2) = 3. Cost = 1 + 3 = 4. Total = 6.
4.  (1,2)[H=8] -> (2,2)[H=9]. Diff=1. <= K(2). Cost = 1. Total = 7.

**Output:**
```text
7
```
