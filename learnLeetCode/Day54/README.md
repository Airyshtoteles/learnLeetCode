# Day 54: Advanced Algorithmic Challenges

## Part 1: Game of Echoing Corridors
**Type:** BFS + Teleportation Logic
**Problem:**
Grid $N \times M$.
- 0: Empty, 1: Wall, 2: Portal.
- **Portal Logic:** Entering a portal teleports you to the *farthest* portal (Manhattan distance). Tie-break: smallest index.
- **Goal:** Min steps $(0,0) \to (N-1, M-1)$.
- **Constraints:** $N, M \le 400$.

## Part 2: Tower Defense: Infernal Pathfinding
**Type:** Dijkstra on Weighted Grid
**Problem:**
Grid $N \times N$. Towers with range and damage.
- **Damage:** Continuous accumulation. Entering a cell adds damage from all covering towers.
- **Goal:** Check if path exists with total damage $\le H$.
- **Constraints:** $N \le 400$.

## Part 3: Fragmented Realms (Dimension Shattered)
**Type:** String Palindrome + Parity Swap
**Problem:**
String $s$, Queries $[l, r, k]$.
- **Operation:** Swap chars at indices with different parity (Even $\leftrightarrow$ Odd). Max $k$ swaps.
- **Goal:** Can $s[l..r]$ become a palindrome?
- **Logic:** Check char counts. Palindrome requires specific parity distribution. Calculate min swaps needed to balance Even/Odd counts.

## Part 4: Last Warrior Standing
**Type:** Simulation + Cycle Detection
**Problem:**
Circular array of Warriors with HP.
- **Round:** Attack next neighbor with $HP/2$. Regenerate damage dealt.
- **End:** Death ($HP \le 0$) or Infinite Loop.
- **Goal:** Index of first dead or -1.

## Part 5: Code Dungeon: Dynamic Rune Forging
**Type:** DAG + Bitmask DP
**Problem:**
DAG nodes with Runes. Runes have dependencies.
- **Rule:** Can pick rune if dependencies in current set.
- **Goal:** Max runes at end.
- **Logic:** DP state `(node, mask)`. Prune subsets.
