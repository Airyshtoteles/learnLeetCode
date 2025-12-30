# Day 56: Advanced Algorithmic Challenges

## 1. Quantum Phase Maze
**Problem:**
Navigate an $N \times M$ maze where cells toggle between "wall" and "path" phases every $K$ steps.
- Phase 0: Active for steps $[0, K-1], [2K, 3K-1], \dots$
- Phase 1: Active for steps $[K, 2K-1], [3K, 4K-1], \dots$
- You can only enter a cell if it is a "path" in the current phase.
- Find the minimum steps to reach $(N-1, M-1)$.

**Constraints:**
- $N, M \le 300$
- $K \le 10^9$

## 2. Necromancer’s Command Chain
**Problem:**
Control $N$ units on a graph with global 'move' or 'wait' commands.
- Units have deterministic "move" targets.
- Find the minimum length command sequence to make all units meet at the same node.
- Return -1 if impossible.

**Constraints:**
- $N \le 2000$
- Graph nodes $\le 2000$

## 3. Echo Strike Arena
**Problem:**
Grid $N \times M$ with enemies.
- Arrows reflect off walls (max 2 reflections).
- You can shoot from a fixed position in 4 cardinal directions.
- Find the minimum number of arrows to kill all enemies.

**Constraints:**
- $N, M \le 300$
- Enemies $\le 300$

## 4. Spirit-Swap Avalanche
**Problem:**
$R \times C$ puzzle grid.
- Swap 2 adjacent tiles once.
- If a connected component has sum $\ge T$, it is destroyed.
- Tiles fall (gravity), potentially creating chains.
- Maximize total value destroyed.

**Constraints:**
- $R, C \le 15$
- $T \le 10^6$

## 5. Chrono-Stamina Tactical Duel
**Problem:**
Turn-based duel.
- You have Stamina $S$, Enemy has $E$.
- Moves have `cost`, `drain` (steals stamina), and `delay`.
- Minimize actions to reduce Enemy Stamina to $\le 0$.

**Constraints:**
- $S, E \le 10^9$
- $P \le 200$
