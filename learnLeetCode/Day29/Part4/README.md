# Tower Game: Destruction Order

There are n towers with heights `height[i]`. One shot destroys the chosen tower and also its immediate neighbors that are strictly smaller than it (at most two: left and right). Find the minimum number of shots to destroy all towers.

## Approach (Greedy by Height Descending)
- Sort indices by height descending.
- Keep a `removed[]` array. For each index in that order, if not removed:
  - Take one shot; mark it removed.
  - If left neighbor exists, not removed, and `height[left] < height[i]`, mark removed.
  - Same for right neighbor.
- This is optimal because a shorter tower never removes a taller one; shooting taller towers first maximizes collateral removals.

## Files
- `tower_game.cpp` — C++17 implementation
- `tower_game.py` — Python implementation
