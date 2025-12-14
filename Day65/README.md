# Day 65: Advanced Algorithms & Optimization

## Part 1: Shadow Clone Cooldown
**Problem:** Find the maximum number of clones that can be active simultaneously such that every pair has coprime cooldowns.
**Solution:** Modeled as a Maximum Clique problem on a graph where edges represent coprime pairs. Used a recursive backtracking algorithm with pruning.
**File:** `Part1/shadow_clone.cpp`

## Part 2: Procedural Dungeon Collapse
**Problem:** Navigate a grid where crumbling tiles toggle between safe and unsafe states every turn.
**Solution:** BFS on state `(row, col, time % 2)`. Handled waiting and moving constraints based on time parity.
**File:** `Part2/dungeon_collapse.cpp`

## Part 3: Boss Pattern Recognition
**Problem:** Check if string B appears as a subsequence in string A with indices forming an arithmetic progression.
**Solution:** Brute force iteration over all possible start indices and common differences. Optimized for small constraints.
**File:** `Part3/boss_pattern.cpp`

## Part 4: Energy Link Optimization
**Problem:** Maximize pairs of nodes with value difference exactly K.
**Solution:** Greedy matching using frequency map. Iterated through sorted values and paired `v` with `v+K` whenever possible.
**File:** `Part4/energy_link.cpp`

## Part 5: Turn Order Permutation
**Problem:** Maximize the number of units that improve their turn rank by modifying speeds with a total budget K.
**Solution:** Dynamic Programming. Partitioned the sorted units into segments where one "loser" is jumped by multiple "winners". $O(N^3)$ with pruning.
**File:** `Part5/turn_order.cpp`
