# Game Map Compression

Difficulty: Hard — Graph / BFS / State Compression

Given an `n x m` grid with:
- `.` empty
- `#` wall
- `K` key (multiple)
- `D` door (can pass only after ALL keys are collected)

Start at `(0,0)` and reach `(n-1,m-1)`. You must collect all keys; doors become passable only when all keys are collected. Return the minimum steps or `-1` if impossible.

## Approach (BFS with Key Bitmask)
- Scan the grid, index each `K` with a bit id `0..k-1`.
- BFS state: `(r, c, mask)` where `mask` holds collected keys.
- Movement rules:
  - Can't enter `#`.
  - Entering `K` sets the corresponding bit in `mask`.
  - Entering `D` is allowed only if `mask == allKeysMask`.
- Stop when we pop `(n-1, m-1, mask)` for any `mask` (but feasibility of passing `D` is handled when moving).

Time: `O(n*m*2^k)`, Space: `O(n*m*2^k)` with `k ≤ 10`.
