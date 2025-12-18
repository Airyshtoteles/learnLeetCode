# Day 68: Advanced Game Mechanics & Optimization

## Part 1: Stamina Lock System
**Problem:** Check if total stamina cost exceeds initial stamina.
**Solution:** Simple sum comparison. `S > sum(cost)`.
**Files:** `Part1/stamina_lock.cpp`, `Part1/stamina_lock.py`

## Part 2: Enemy Fusion Order
**Problem:** Minimize final enemy strength by fusing adjacent enemies `max(a, b) + 1`.
**Solution:** Interval Dynamic Programming (Range DP). `dp[i][j] = min(max(dp[i][k], dp[k+1][j]) + 1)`.
**Files:** `Part2/enemy_fusion.cpp`, `Part2/enemy_fusion.py`

## Part 3: Quest Deadline Shuffle
**Problem:** Maximize reward from quests with deadlines, each taking 1 unit time.
**Solution:** Greedy with Min-Heap. Sort by deadline, maintain heap of rewards for selected tasks. If heap size exceeds deadline, remove smallest reward.
**Files:** `Part3/quest_deadline.cpp`, `Part3/quest_deadline.py`

## Part 4: Map Rotation Escape
**Problem:** Navigate grid where map rotates 180 degrees every 2 steps.
**Solution:** BFS with state `(row, col, steps % 4)`. Handle coordinate transformations for rotation events.
**Files:** `Part4/map_rotation.cpp`, `Part4/map_rotation.py`

## Part 5: Inventory Auto-Sort
**Problem:** Minimum operations to sort string where operation is "sort any substring".
**Solution:** If already sorted, 0. Else 1 (sort entire string).
**Files:** `Part5/inventory_sort.cpp`, `Part5/inventory_sort.py`

## Part 6: Boss Enrage Threshold
**Problem:** Minimize attacks to defeat boss where damage doubles every `k` total damage.
**Solution:** Greedy. Use largest damage attacks first to reach thresholds and maximize multiplier benefit.
**Files:** `Part6/boss_enrage.cpp`, `Part6/boss_enrage.py`
