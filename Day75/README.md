# Day 75: Game Mechanics & Strategic Optimization

Today's challenges focus on strategic decision-making, time-based mechanics, and optimization algorithms.

## Part 1: Critical Hit Window
**Problem:** Maximize total damage by pairing attacks to trigger critical hits.
- **Input:** Damage array `d[]`, Window array `w[]`.
- **Logic:** Sort attacks by damage descending. Pair them sequentially to maximize critical damage. For pairs $(d_i, d_{i+1})$, set the second attack as critical: total = $d_i + 2 \cdot d_{i+1}$.
- **Solution:** [C++](./Part1/critical_hit.cpp) | [Python](./Part1/critical_hit.py)

## Part 2: Moving Platform Drift
**Problem:** Determine if character can reach the last platform while they move over time.
- **Input:** Positions `pos[]`, Velocities `v[]`, Jump distance `D`.
- **Logic:** BFS with state (platform, time). At each time $t$, check if any two platforms are within distance $D$ (considering their positions: $pos[i] + v[i] \cdot t$).
- **Solution:** [C++](./Part2/platform_drift.cpp) | [Python](./Part2/platform_drift.py)

## Part 3: Potion Mixing Table
**Problem:** Find maximum potion level achievable by repeatedly mixing with GCD operation.
- **Input:** Potion levels `a[]`.
- **Logic:** Mixing two potions with levels $x$ and $y$ produces $\gcd(x, y)$. The result of any sequence of mixings is the GCD of all selected potions. Maximum is $\gcd(a_0, a_1, \ldots, a_{n-1})$.
- **Solution:** [C++](./Part3/potion_mixing.cpp) | [Python](./Part3/potion_mixing.py)

## Part 4: Trap Activation Order
**Problem:** Find maximum number of traps that can be activated, where traps spread to adjacent ones.
- **Input:** Trap array `t[]` (0/1).
- **Logic:** Find the longest contiguous segment of 1s. Traps spread to neighbors, so only contiguous 1s can be activated together.
- **Solution:** [C++](./Part4/trap_activation.cpp) | [Python](./Part4/trap_activation.py)

## Part 5: Dialogue Choice Compression
**Problem:** Minimize string length by removing all occurrences of one character.
- **Input:** String `s`.
- **Logic:** Count character frequencies. To minimize length, remove the most frequent character. Result = $|s| - \max(\text{frequency})$.
- **Solution:** [C++](./Part5/dialogue_compression.cpp) | [Python](./Part5/dialogue_compression.py)

## Part 6: Endless Wave Scheduler
**Problem:** Determine if player can survive all enemy waves with limited defeat capacity.
- **Input:** Enemy power `p[]`, Defeat capacity `K`, Max active power `S`.
- **Logic:** Simulation. For each wave, add power to active pool, then defeat up to $K$ power. Check if active power exceeds $S$ at any point.
- **Solution:** [C++](./Part6/endless_wave.cpp) | [Python](./Part6/endless_wave.py)
