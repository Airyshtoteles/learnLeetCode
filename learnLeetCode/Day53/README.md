# Day 53: Advanced Algorithmic Challenges

## Part 1: Shadow Corridor Escape
**Type:** Pathfinding + Dynamic Constraints
**Problem:**
Navigate an $N \times M$ grid from $(0,0)$ to $(N-1, M-1)$.
- **Shadow:** `shadow_time[i][j] = (i + j) % K`.
- **Death:** If you enter $(i, j)$ at time $t$ and `t % K == shadow_time[i][j]`, you die.
- **Moves:** Up, Down, Left, Right, Wait. All cost 1.
- **Goal:** Minimum time to reach end.

## Part 2: Arcane Damage Compression
**Type:** Greedy + Data Structures
**Problem:**
Array $A$ of length $N$. Max $K$ operations.
- **Operation:** Merge adjacent $A[i], A[i+1]$ into $A[i] \oplus A[i+1]$.
- **Goal:** Minimize sum of final array.
- **Constraints:** $N \le 2 \cdot 10^5$.

## Part 3: Infinite Jump Platform
**Type:** Graph Construction + BFS
**Problem:**
Platforms $0 \dots N-1$.
- **Moves:** $i \to i \pm jump[i]$ (Cost 1).
- **Warp:** $i \to j$ if $jump[i] == jump[j]$ (Cost 1).
- **Goal:** Min cost to $N-1$.
- **Constraints:** $N \le 3 \cdot 10^5$.

## Part 4: Elemental Chess Dominion
**Type:** Simulation + Bitmasking + Optimization
**Problem:**
$N \times N$ board. Count safe cells.
- **Kings:**
  - Fire: Row attack.
  - Water: Column attack.
  - Earth: Diagonal attack.
  - Air: Euclidean radius $R$ attack.
- **Constraints:** $N \le 3 \cdot 10^5$.

## Part 5: Dungeon Energy Balancer
**Type:** Greedy + DSU (Scheduling)
**Problem:**
$N$ rooms, $T$ steps.
- Room $i$: `gain`, `cost`, `cooldown`.
- **Goal:** Maximize total energy.
- **Constraint:** Can't visit room $i$ again for `cooldown[i]` steps.
- **Constraints:** $N \le 2000, T \le 10^6$.
