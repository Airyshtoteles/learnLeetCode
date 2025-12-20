# Day 70: Game Logic & Simulation

Today's challenges focus on implementing various game mechanics and logic systems, ranging from difficulty adjustment to pathfinding and turn management.

## Part 1: Adaptive Difficulty Curve
**Problem:** Calculate the minimum final difficulty level after a series of wins and losses.
- **Input:** Initial difficulty, list of outcomes (1 for win, -1 for loss).
- **Logic:** Assumed optimal strategy (or simple simulation) where losses decrease difficulty and wins increase it, clamped at 0.
- **Solution:** [C++](./Part1/adaptive_difficulty.cpp) | [Python](./Part1/adaptive_difficulty.py)

## Part 2: Boss Phase Trigger
**Problem:** Determine if a boss's health thresholds for phase changes are all unique.
- **Input:** List of health percentages.
- **Logic:** Use a Set to check for duplicates.
- **Solution:** [C++](./Part2/boss_phase.cpp) | [Python](./Part2/boss_phase.py)

## Part 3: Item Durability Chain
**Problem:** Find the minimum remaining items after a chain reaction of durability reduction, with the option to remove one item beforehand.
- **Input:** List of item durabilities.
- **Logic:** Stack-based simulation (similar to asteroid collision or candy crush). Brute-force removing each item to find the optimal starting state.
- **Solution:** [C++](./Part3/item_durability.cpp) | [Python](./Part3/item_durability.py)

## Part 4: Fog Memory Path
**Problem:** Find the shortest path through a grid with obstacles (fog of war).
- **Input:** Grid dimensions and layout (0 for path, 1 for wall).
- **Logic:** Breadth-First Search (BFS) to find the shortest path distance.
- **Solution:** [C++](./Part4/fog_path.cpp) | [Python](./Part4/fog_path.py)

## Part 5: Spell Charge Scheduling
**Problem:** Calculate the total time required to cast a sequence of spells that must be charged sequentially.
- **Input:** List of charge times.
- **Logic:** Summation of all charge times.
- **Solution:** [C++](./Part5/spell_charge.cpp) | [Python](./Part5/spell_charge.py)

## Part 6: Turn Priority Inversion
**Problem:** Calculate the total number of turns until all entities have 0 priority, where priority halves each turn.
- **Input:** List of priority values.
- **Logic:** Simulation of halving process for each entity. Total turns is the sum of steps for each entity to reach 0.
- **Solution:** [C++](./Part6/turn_priority.cpp) | [Python](./Part6/turn_priority.py)
