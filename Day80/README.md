# Day 80: Advanced Optimization & Simulation

This day focuses on complex optimization problems, simulation, and graph theory with state.

## Part 1: Shadow Clone Allocation
**Problem:** Minimize the maximum time required to complete `n` missions using `k` clones. Clones can be assigned any set of missions.
**Solution:** This is the **Load Balancing Problem** (or Bin Packing optimization). We use **Binary Search on the Answer**. To check if a time limit `T` is feasible, we try to distribute tasks into `k` buckets of capacity `T`. We use a **First Fit Decreasing** greedy heuristic (or backtracking for small N) to check feasibility.
- [C++ Solution](Part1/shadow_clone.cpp)
- [Python Solution](Part1/shadow_clone.py)

## Part 2: HP Swap Spell
**Problem:** Determine if all monsters can be defeated given a damage limit (implicit). You can swap the HP of two monsters once.
**Solution:** We model this as minimizing total damage taken, where damage is proportional to the time a monster stays alive. We calculate the initial damage and then iterate through all pairs to find the swap that maximizes the reduction in total damage.
- [C++ Solution](Part2/hp_swap.cpp)
- [Python Solution](Part2/hp_swap.py)

## Part 3: Portal With Memory
**Problem:** Reach a target in a grid where 'P' portals bounce you back to your previous position.
**Solution:** Since the portal forces you back to the visited cell you came from, it effectively acts as a dead end or wall (unless it's the only way to return to a junction, but visited states prevent loops). We treat 'P' as an obstacle and run **BFS**.
- [C++ Solution](Part3/portal_memory.cpp)
- [Python Solution](Part3/portal_memory.py)

## Part 4: Combo Multiplier Decay
**Problem:** Maximize score from a string where strictly increasing characters boost combo, otherwise combo halves.
**Solution:** We construct the string in "layers". Each layer consists of one of each available distinct character, sorted ascending. This maximizes the length of increasing sequences and minimizes the penalty of resetting.
- [C++ Solution](Part4/combo_decay.cpp)
- [Python Solution](Part4/combo_decay.py)

## Part 5: Weapon Durability Path
**Problem:** Find if a target is reachable in a weighted graph with weapon durability. You can repair the weapon once.
**Solution:** **Dijkstra's Algorithm** with state. The state is `(node, repaired_status)`. We track the maximum durability remaining at each node for both states (repaired and not repaired).
- [C++ Solution](Part5/weapon_path.cpp)
- [Python Solution](Part5/weapon_path.py)

## Part 6: Enemy Spawn Compression
**Problem:** Count final enemies if enemies spawning within `k` time of each other merge.
**Solution:** **Greedy / Clustering**. We sort the spawn times and iterate. If `t[i] - last_t <= k`, they merge (and `last_t` updates to `t[i]`, extending the chain). Otherwise, a new enemy group starts.
- [C++ Solution](Part6/spawn_compression.cpp)
- [Python Solution](Part6/spawn_compression.py)
