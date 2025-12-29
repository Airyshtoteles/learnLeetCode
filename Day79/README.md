# Day 79: Advanced Game Mechanics & Optimization

This day focuses on solving complex algorithmic problems related to game mechanics, resource management, and optimization.

## Part 1: Time Frozen Enemies
**Problem:** Maximize the number of enemies defeated within a time limit `T` and damage capacity `D`.
**Solution:** Greedy approach. Sort enemies by HP ascending. Defeat the weakest ones first to maximize the count.
- [C++ Solution](Part1/time_frozen.cpp)
- [Python Solution](Part1/time_frozen.py)

## Part 2: Infinite Jump Tiles
**Problem:** Determine if it's possible to reach the end of a tile array where `tiles[i]` is the max jump length. You can change one tile's value to infinity.
**Solution:** If we can change one tile, we can change the starting tile `tiles[0]` to infinity, allowing us to jump directly to the end. The answer is always true (assuming `n > 0`).
- [C++ Solution](Part2/infinite_jump.cpp)
- [Python Solution](Part2/infinite_jump.py)

## Part 3: Skill Cooldown Permutation
**Problem:** Find the minimum time to use `n` distinct skills, where each skill has a cooldown `C`.
**Solution:** Since all skills are distinct, we can use them one after another without waiting for any cooldown (cooldowns only apply to reusing the *same* skill). The time is simply `n`.
- [C++ Solution](Part3/skill_cooldown.cpp)
- [Python Solution](Part3/skill_cooldown.py)

## Part 4: Dynamic Boss Shield
**Problem:** A boss has a shield that regenerates. You need `H` hits to break it. After a hit, you must wait `k` seconds before the next hit counts. Calculate total time.
**Solution:** You need `H` hits. The first hit is at time 0. You wait `k` seconds `H-1` times. Total time = `(H - 1) * k`.
- [C++ Solution](Part4/dynamic_shield.cpp)
- [Python Solution](Part4/dynamic_shield.py)

## Part 5: Dungeon Collapse
**Problem:** In a tree structure representing a dungeon, destroying a node collapses it and all its ancestors. Find the minimum nodes to destroy to collapse the root.
**Solution:** Destroying any node collapses the path to the root. To collapse the root, we only need to destroy one node (the root itself, or any child which triggers the chain). Minimum is 1.
- [C++ Solution](Part5/dungeon_collapse.cpp)
- [Python Solution](Part5/dungeon_collapse.py)

## Part 6: Mana Redistribution
**Problem:** Maximize the minimum mana among mages by redistributing mana. You can move mana from one mage to another at most `k` times.
**Solution:** Binary Search on the Answer. We check if a target minimum value `X` is possible by calculating the mana `needed` by poor mages and `available` from rich mages. Condition: `needed <= available` and `needed <= k`.
- [C++ Solution](Part6/mana_redistribution.cpp)
- [Python Solution](Part6/mana_redistribution.py)
