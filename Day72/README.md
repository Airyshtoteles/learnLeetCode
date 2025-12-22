# Day 72: Procedural Generation & Game States

Today's challenges focus on procedural generation constraints, state management, and optimization problems within game contexts.

## Part 1: Random Seed Consistency
**Problem:** Find the longest subsequence of seeds where each subsequent seed is a multiple of the previous one.
- **Input:** List of seeds.
- **Logic:** Dynamic Programming (Longest Divisible Subsequence). For each number, check its divisors to extend the longest chain found so far.
- **Solution:** [C++](./Part1/random_seed.cpp) | [Python](./Part1/random_seed.py)

## Part 2: Health Bar Segmentation
**Problem:** Count ways to cut a binary string such that every segment has an even number of '1's.
- **Input:** Binary string `s`.
- **Logic:** A cut is valid at index `i` if the prefix `s[0...i]` contains an even number of '1's. If total '1's is odd, 0 ways. Otherwise, $2^K$ where $K$ is the number of valid internal cut positions.
- **Solution:** [C++](./Part2/health_segment.cpp) | [Python](./Part2/health_segment.py)

## Part 3: Ability Upgrade Tree
**Problem:** Select a set of nodes in a tree such that no two are ancestor/descendant, maximizing total value.
- **Input:** Tree structure and node values.
- **Logic:** Tree DP. For each node, decide whether to pick it (blocking all descendants) or not (summing results from children). $DP[u] = \max(v[u], \sum DP[child])$.
- **Solution:** [C++](./Part3/upgrade_tree.cpp) | [Python](./Part3/upgrade_tree.py)

## Part 4: Boss Damage Reflection
**Problem:** Determine if it's possible to reduce Boss HP to exactly 0 without it becoming negative.
- **Input:** Boss HP `H`.
- **Logic:** Since we can deal any integer damage, we can always deal 1 damage repeatedly to reach 0 exactly, provided $H \ge 0$.
- **Solution:** [C++](./Part4/boss_reflection.cpp) | [Python](./Part4/boss_reflection.py)

## Part 5: NPC Patrol Shift
**Problem:** Count collisions between NPCs moving on a line (reversing on collision).
- **Input:** Positions and directions.
- **Logic:** Treat NPCs as passing through each other. A collision occurs between any pair $(i, j)$ where $pos[i] < pos[j]$, $dir[i] = Right$, and $dir[j] = Left$.
- **Solution:** [C++](./Part5/npc_patrol.cpp) | [Python](./Part5/npc_patrol.py)

## Part 6: Save File Rollback
**Problem:** Find the maximum length of a strictly increasing prefix after deleting a suffix.
- **Input:** Array `a`.
- **Logic:** Simply find the length of the longest strictly increasing prefix of the original array.
- **Solution:** [C++](./Part6/save_rollback.cpp) | [Python](./Part6/save_rollback.py)
