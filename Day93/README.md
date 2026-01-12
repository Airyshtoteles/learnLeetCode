# Day 93: Strategic Systems & Theoretical Constraints

This day explores problems involving resource management, game theory, and number theoretic constraints.

## Problems

### 1. Boss With Sliding Window Immunity
**Concept:** Sliding Window Logic + Greedy Optimization.
**Goal:** Minimize attacks to kill a boss that ignores `Max(Window)` damage.
**Solution:** `Max_Damage` strategy. Moves = `ceil(H/D) + K`.

### 2. Dungeon With Energy That Remembers
**Concept:** State Dominance Pruning.
**Goal:** Reach destination without visiting a cell with less-or-equal energy than before.
**Solution:** BFS with strict check `if (new_energy > visited_energy[r][c])`.

### 3. Skill DAG With Limited Reuse
**Concept:** Shortest Path on DAG.
**Goal:** Reach Target Skill `T` within `K` total skills taken.
**Solution:** BFS from root nodes. Distance = Skills needed.

### 4. Infinite Damage With GCD Trap
**Concept:** Number Theory (Frobenius/GCD).
**Goal:** Deal damage >= H. Boss immune if GCD(used) != 1.
**Solution:** Check `GCD(All_Available) == 1`. If yes, infinity reachable.

### 5. Multi-Agent Dungeon With Shared Cooldown
**Concept:** Independent Agent Reachability.
**Goal:** One of K agents reaches target. Global cooldown dilates time but doesn't block independent pathing.
**Solution:** Check if `dist(Agent_i -> Target)` is finite for any `i`.

### 6. Economy With Delayed Transactions
**Concept:** Positive Cycle / Investment ROI.
**Goal:** Reach wealth `W_Target`.
**Solution:** Check if `W_Initial >= W_Target` OR potentially strictly profitable deal (`Gain > Cost`) is affordable (`W_Init >= Cost`).
