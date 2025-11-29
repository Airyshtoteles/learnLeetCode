# Day 51 Part 3: Quantum Nim

## Problem Description
In the quantum realm, piles of energy stones are entangled. You are playing a game against a cosmic entity.

There are $N$ piles of stones, with initial counts $A_1, A_2, \dots, A_N$.
There are entanglement links between some piles, forming a graph.

A "Quantum Move" consists of:
1. Choosing a pile $i$ and a number of stones $k > 0$.
2. Removing $k$ stones from pile $i$.
3. Due to entanglement, $k$ stones are also removed from all piles $j$ that are directly connected to pile $i$.
4. The move is valid only if pile $i$ and all its neighbors have at least $k$ stones.

The game ends when a player cannot make a valid move. The last player to move wins (Normal Play).

## Input Format
- `stones`: List of integers representing initial stones in each pile.
- `edges`: List of pairs `(u, v)` representing entanglement links.

## Constraints
- $N \le 15$
- $A_i \le 100$
- The graph can be arbitrary.

## Strategy
This is an impartial game, so we can use the **Sprague-Grundy Theorem**.
The state is defined by the tuple of stone counts $(A_1, \dots, A_N)$.
We need to compute the Grundy value (or nim-value) $G(state)$.
- If $G(state) > 0$, the first player (Next) has a winning strategy.
- If $G(state) = 0$, the second player (Previous) wins.

$G(state) = \text{mex}(\{G(next\_state) \mid next\_state \text{ is reachable from } state\})$

### Optimization
- Since $N$ is small (15), but $A_i$ is up to 100, the state space is huge ($100^{15}$).
- However, the game is finite and strictly decreasing.
- Is there a simplified property?
- Notice that a move on pile $i$ subtracts $k$ from a specific subset of piles (mask $M_i$).
- This is a **Vector Subtraction Game**.
- If the game decomposes into independent subgames, we can XOR their Grundy values.
- But here, the moves overlap (a pile can be affected by its own move or a neighbor's move).
- So the piles are NOT independent.
- However, maybe we can view this as a game on the *moves*?
- No.

### Memoization with Pruning
- We can use memoization.
- But we need to handle the large state space.
- Maybe the number of reachable states is small?
- Or maybe we can solve it for small $N$ and observe a pattern?
- Actually, for $N \le 15$, we probably need a more efficient approach than raw memoization if $A_i$ is large.
- But wait, is it possible that the game is equivalent to Nim with a transformed basis?
- If the allowed move vectors $v_1, \dots, v_N$ are linearly independent (over $\mathbb{R}$? No, over what?), maybe we can transform the state?
- In standard Nim, moves are $e_1, e_2, \dots, e_N$ (unit vectors).
- Here, moves are $v_i = e_i + \sum_{j \in adj(i)} e_j$.
- If we can remove $k$ times $v_i$, this is exactly Nim played on the coordinates in the basis $\{v_i\}$.
- **Hypothesis:** If the vectors $\{v_i\}$ form a basis, the game is equivalent to Nim with pile sizes $c_1, \dots, c_N$ where $State = \sum c_i v_i$.
- If they don't form a basis (dependent), it's more complex.
- But wait, we can only remove $k > 0$. In transformed coordinates, we might need to remove positive amounts.
- If the transformation matrix $M$ (where columns are $v_i$) has a non-negative inverse, then any state $S$ corresponds to non-negative $c = M^{-1} S$.
- Then a move on pile $i$ corresponds to reducing $c_i$ by $k$.
- This would make it exactly Nim with piles $c_i$.
- **Check:**
  - Move $i$: $S \to S - k v_i$.
  - In $c$-space: $Mc \to M(c - k e_i)$.
  - So $c \to c - k e_i$.
  - This is exactly removing $k$ from the $i$-th component.
  - The condition "valid only if all affected piles have $\ge k$" translates to $S \ge k v_i$.
  - In $c$-space, this means $M c \ge k v_i$.
  - This is NOT just $c_i \ge k$. It's a complex constraint on $c$.
  - So the "Basis Transformation" doesn't fully simplify the validity check.

### Backtracking / Minimax with Alpha-Beta?
- Since we just need to know if we can win, we can use Minimax (returns Win/Loss).
- With memoization.
- For $N=15$, maybe too slow.
- Let's assume $N$ is smaller for the "Hard" version, or the constraints allow a specific solution.
- Let's stick to Memoization for small inputs ($N \le 5, A_i \le 10$) for testing, and try to implement a general solver.
- Or maybe the problem implies $N$ is very small (e.g. 3-5).
- I'll implement a Memoized Solver.

