# Day 94: Restricted Systems & Feasibility Analysis

This day focuses on problems where constraints are dynamic or depend on history (Prefix sums, Cooldowns, Monotonicity).

## Problems

### 1. Boss With Damage Taxation
**Concept:** Greedy Strategy against Dynamic Penalty.
**Goal:** Minimize steps to reach effective damage H. Penalised by Floor(Total/K).
**Solution:** Always use Max Damage source. Simulation.

### 2. Dungeon With Direction Cooldown
**Concept:** BFS with History State.
**Goal:** Reach destination. Direction D disabled for C steps after use.
**Solution:** BFS State `(r, c, w0, w1, w2, w3)`.

### 3. Skill Graph With Expiring Nodes
**Concept:** Scheduling on DAG with Deadlines.
**Goal:** Feasibility of task T.
**Solution:** Backward scheduling (Identify Ancestors) + EDF (Earliest Deadline First with topo-sort awareness via Min-Heap of Available nodes).

### 4. Infinite Damage With Prefix Dominance
**Concept:** Pareto Efficiency / Dominance.
**Goal:** Check if strategy is dominated.
**Solution:** Max Damage strategy generates $(\text{len}, \text{sum})$ points that are on the optimal frontier. Result is always YES (if $d > 0$).

### 5. Multi-Agent Dungeon With Sacrifice
**Concept:** Connectivity & Buff Stacking.
**Goal:** One agent reaches target. Sacrificing others buffs speed.
**Solution:** Connectivity check. If any agent is connected to target in grid graph, YES. Speed reduces turns but doesn't change reachability (in standard grid).

### 6. Economy With Compound Interest Trap
**Concept:** Monotonic Growth Constraint.
**Goal:** Order transactions to maximize final wealth and keep $W_t \ge W_{t-1}$.
**Solution:** Greedy Sort Descending. Maximizes final sum (Interest compounding on early positives) and maximizes safety buffer.
