# Day 73: Optimization & Simulation

Today's challenges focus on optimizing game mechanics, including replay buffers, damage thresholds, state oscillations, and pathfinding.

## Part 1: Ghost Replay Buffer
**Problem:** Maximize replay length by skipping exactly one continuous segment.
- **Input:** Array of moves.
- **Logic:** To maximize the remaining length $N - L$, we minimize the skipped length $L$. The shortest non-empty segment has length 1. Result is $N-1$.
- **Solution:** [C++](./Part1/ghost_replay.cpp) | [Python](./Part1/ghost_replay.py)

## Part 2: Armor Break Threshold
**Problem:** Determine if Boss can be defeated in $\le X$ attacks, where damage is halved if Armor $> 0$.
- **Input:** Damages `d[]`, Armor `A`, Max attacks `X`.
- **Logic:** Sort `d` descending. Use the top $k$ attacks ($k \le X$). The optimal strategy is to use the largest damage as the "finisher" (full damage) and others as "breakers" (halved). Check if sum $\ge A$.
- **Solution:** [C++](./Part2/armor_break.cpp) | [Python](./Part2/armor_break.py)

## Part 3: Combo Gauge Oscillation
**Problem:** Calculate the number of unique states in a gauge system where $val \to val+a$ or $val \to val-b$.
- **Input:** $a, b$.
- **Logic:** The process $x_{n+1} = (x_n + a) \pmod{a+b}$ visits all multiples of $\gcd(a, b)$ modulo $a+b$. The number of unique states is $(a+b) / \gcd(a, b)$.
- **Solution:** [C++](./Part3/combo_gauge.cpp) | [Python](./Part3/combo_gauge.py)

## Part 4: Map Reveal Order
**Problem:** Maximize revealed cells where revealing requires Power $\ge$ Cell Value.
- **Input:** Grid.
- **Logic:** Start at the cell with the maximum value (highest initial power). Use a Priority Queue (Prim's Algorithm style) to greedily reveal the smallest accessible neighbors.
- **Solution:** [C++](./Part4/map_reveal.cpp) | [Python](./Part4/map_reveal.py)

## Part 5: Inventory Weight Shift
**Problem:** Determine if item weights can be equalized.
- **Input:** Weights `w[]`.
- **Logic:** Possible if and only if the total weight is divisible by the number of items.
- **Solution:** [C++](./Part5/inventory_shift.cpp) | [Python](./Part5/inventory_shift.py)

## Part 6: Time Attack Checkpoint Skip
**Problem:** Minimize arrival time at the last checkpoint by skipping one intermediate checkpoint.
- **Input:** Checkpoint times `t[]`.
- **Logic:** Arrival time is $\max(t_{path})$. Skipping a checkpoint removes it from the max set. We should remove the largest intermediate value. Result is $\max(t_{start}, t_{end}, \text{second\_largest\_intermediate})$.
- **Solution:** [C++](./Part6/checkpoint_skip.cpp) | [Python](./Part6/checkpoint_skip.py)
