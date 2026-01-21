# Day 96: Advanced Optimization, Graph Theory & Simulations

## Part 1: Boss With Adaptive Threshold
**Problem:** Boss adapts to damage. Threshold $T$ rises to $D$ if $D > T$. Effective damage $\max(0, D-T)$.
**Logic:** 
Any strictly increasing sequence $d_1 < d_2 < \dots < d_k$ yields total damage equal to $d_k$ (Max element) due to telescoping sum: $(d_1) + (d_2-d_1) + \dots = d_k$.
Non-increasing sequences yield 0.
Thus, total possible damage is `Max(Available_Damage)`.
We just need to check if `Max >= HP`.

## Part 2: Dungeon With Rotating Gravity
**Problem:** Gravity rotates 90 degrees every K steps. Player falls until hitting wall. Min steps to reach target?
**Logic:**
Dijkstra on State `(r, c, phase)`. Phase tracks gravity direction implicitly via `time`.
Since falling is instantaneous/compulsory, edges represent "Move 1 step -> Phase Check -> Gravity Fall".
We assume checking state `(r, c, time % 4K)` handles cycles.

## Part 3: Skill DAG With Partial Refund
**Problem:** Skill Tree. Cost to enter node. Refund after completing children children.
**Logic:**
Recursive Greedy / Job Sequencing.
Each subtree is reduced to `(PeakNeed, NetReturn)`.
To optimally process children:
- Positive Net Return: Sort by `Peak` Ascending (easiest first).
- Negative Net Return: Sort by `Peak + Net` Descending (keep high resources longest).
Then verify if `Initial Energy >= Peak(Target)`.

## Part 4: Infinite Damage With Growth Ceiling
**Problem:** Maintain non-decreasing average damage.
**Logic:**
If we can pick any damage $d \in D$ repeatedly:
Picking $d_{max}$ repeatedly yields constant average $d_{max}$.
Conditions satisfy $Avg_k \ge Avg_{k-1}$.
Thus, if $d_{max} > 0$, we can accumulate infinite damage.
Answer YES if `Max(D) > 0`.

## Part 5: Multi-Agent Dungeon With Communication Delay
**Problem:** Agents explore for $t$ steps, then Target revealed. Can they cover all possible targets within Limit?
**Logic:**
Check if we can select $K$ cells, each reachable by an agent in $\le t$ steps, such that these $K$ cells form a Dominating Set (or K-Center cover) of the Safe Cells with radius $Limit - t$.
Implemented with Heuristic Greedy Set Cover.

## Part 6: Economy With Transaction Cooldown Graph
**Problem:** Graph nodes are transactions. Neighbors get cooldown. Reach target Money.
**Logic:**
Dijkstra Search on State `(Node, CooldownsVector)`.
Maximize Money.
Pruning visited states with less money.
Handles small graphs/constraints.
