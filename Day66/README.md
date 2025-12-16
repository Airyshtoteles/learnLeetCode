# Day 66: Simulation & Optimization

## Part 1: Mana Drain Loop
**Problem:** Simulate mage movement with mana drain. Detect if loop stabilizes (visited same index) or mana runs out.
**Solution:** Simulation with `visited` set.
**Files:** `Part1/mana_drain.cpp`, `Part1/mana_drain.py`

## Part 2: Dynamic Quest Chain
**Problem:** Maximize quests completed where quest `i` requires `total_reward >= i`.
**Solution:** Greedy iteration. Since quests are indexed 0 to n-1, we just check condition sequentially.
**Files:** `Part2/quest_chain.cpp`, `Part2/quest_chain.py`

## Part 3: Echo Spell Stack
**Problem:** Calculate total damage where identical consecutive spells merge and double.
**Solution:** Stack-based simulation (similar to 2048 merge logic).
**Files:** `Part3/echo_spell.cpp`, `Part3/echo_spell.py`

## Part 4: AI Path Recalculation
**Problem:** Shortest path on a grid that rotates 90 degrees upon hitting a wall.
**Solution:** Dijkstra's Algorithm on state space `(row, col, rotation)`.
**Files:** `Part4/ai_path.cpp`, `Part4/ai_path.py`

## Part 5: Save Slot Compression
**Problem:** Reduce array to single element using `gcd(a, b)` on adjacent elements to maximize result.
**Solution:** The result is always `gcd` of all elements.
**Files:** `Part5/save_compression.cpp`, `Part5/save_compression.py`
