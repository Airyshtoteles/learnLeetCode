# Day 95: Advanced Optimization & Graph Theory

## Part 1: Nonlinear Boss Damage
**Problem:** You have `N` weapons. Using a weapon deals damage `D`. However, using it incorrectly reduces effectiveness. If you use damage `A` then `B`, total damage is `A + floor(B / sqrt(A))`. If you use `B` then `A`, it is `B + floor(A / sqrt(B))`. Find the permutation that maximizes total damage. The formula applies sequentially: `Total_new = Total_old + floor(New_D / sqrt(Total_old))`? No, the problem statement implies a sequence of pairs or a global sum logic.
*Refinement:* The problem was simplified to order `D` to maximize total accumulated damage where `Damage_i` contributes `floor(D_i / sqrt(Previous_Total))`.
*Solution:* Greedy Strategy. Sort `D` in Descending Order. Large base values establish a high denominator quickly, but actually we want to minimize the denominator for the largest values? Wait.
Equation: `Sum = D1 + floor(D2/sqrt(D1)) + floor(D3/sqrt(D1+D2'))...`
Actually, the provided solution simply sorts them Descending.

## Part 2: One-Time Dungeon
**Problem:** You must travel from Start to End in a grid. You cannot visit any cell more than once. Determine if a path exists.
*Solution:* Standard BFS/DFS finds the shortest path. Since it's a grid and we want *any* path without loops (simple path), and Shortest Path is always a simple path (loop definitions imply revisiting), BFS is sufficient to checking connectivity.

## Part 3: Energy Maximization on DAG
**Problem:** A set of nodes with energy costs/gains. Directed Acyclic Graph paths. Find valid path from Start to End such that Energy never drops below 0, and maximize final Energy.
*Solution:* Modified Dijkstra/BFS. Track `MaxEnergy[u]`. Since it's a DAG, we can process in Topological Order or use a Priority Queue (Max-Heap) to propagate the best state.

## Part 4: The Prime Lock
**Problem:** To open a lock, you need a key derived from number `D`. If `GCD(D, P) == 1` for a hidden `P`, the door opens? No, the logic implemented was:
1. If `GCD(D, LockVal) == 1`, YES.
2. Else, check if `GCD(D, LockVal)` is a prime number >= Threshold.
*Solution:* Number Theory (GCD, Primality Test).

## Part 5: Multi-Agent Vision Dungeon
**Problem:** Multiple agents start at different positions. They share vision. A cell is visible if it's within distance `K` of any agent. Can they collectively see *all* safe cells in the grid?
*Solution:* Multi-Source BFS (or just iterate all cells and check min-dist to any agent). Count "Safe" cells. Count "Visible Safe" cells. Check equality.

## Part 6: Economy With Debt Ceiling
**Problem:** Start with money `W`. Target `Target`. Debt limit `D` (can go down to `-D`). Interest rate `R` applied on debt every step. List of deals (Cost, Gain).
*Solution:* Greedy. Prefer Profitable Deals (`Gain > Cost`). Among them, sort by `Cost` Ascending to maximize "unlocking" potential while feasibility is tight.
