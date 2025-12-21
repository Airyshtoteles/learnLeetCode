# Day 71: Advanced Game Mechanics & Optimization

Today's challenges focus on complex game mechanics, including cooldown management, parity-based pathfinding, string manipulation, and time synchronization.

## Part 1: Auto-Heal Cooldown Conflict
**Problem:** Maximize HP gain by selecting skills with a cooldown constraint based on value difference.
- **Input:** Initial HP, list of heal values.
- **Logic:** The constraint $|t_i - t_j| \ge |h_i - h_j|$ is always satisfiable by scheduling skill $i$ at time $h_i$. Thus, we can use all positive healing skills.
- **Solution:** [C++](./Part1/auto_heal.cpp) | [Python](./Part1/auto_heal.py)

## Part 2: Dungeon Room Parity
**Problem:** Determine reachability of the last room where entry depends on parity matching.
- **Input:** List of room values.
- **Logic:** BFS. After the first move, the running sum is always even, restricting movement to rooms with even values only.
- **Solution:** [C++](./Part2/dungeon_parity.cpp) | [Python](./Part2/dungeon_parity.py)

## Part 3: Combo String Reforge
**Problem:** Minimum operations to make all characters in a string identical, using a "remove left, double right" mechanic.
- **Input:** String `s`.
- **Logic:** We can only convert the string to the character currently at the end. Cost is the count of non-matching characters.
- **Solution:** [C++](./Part3/combo_reforge.cpp) | [Python](./Part3/combo_reforge.py)

## Part 4: Boss Arena Shrink
**Problem:** Reach the boss in a grid where the outer layer collapses every $k$ steps.
- **Input:** Grid size, start/boss pos, $k$.
- **Logic:** BFS with time-dependent validity check. The valid range shrinks over time.
- **Solution:** [C++](./Part4/boss_arena.cpp) | [Python](./Part4/boss_arena.py)

## Part 5: Skill Synergy Collapse
**Problem:** Maximize skill power by merging adjacent equal skills, with one optional removal.
- **Input:** List of skill powers.
- **Logic:** Iterate through removing each skill. For each state, simulate the collapse using a stack (similar to "2048" or bracket matching) to find the maximum obtainable value.
- **Solution:** [C++](./Part5/skill_synergy.cpp) | [Python](./Part5/skill_synergy.py)

## Part 6: Time Warp Checkpoints
**Problem:** Minimum time to reach the last checkpoint, where each checkpoint locks you until a specific time.
- **Input:** List of checkpoint times.
- **Logic:** The arrival time at checkpoint $i$ is determined by the maximum of all previous lock times. The final time is the maximum value in the array.
- **Solution:** [C++](./Part6/time_warp.cpp) | [Python](./Part6/time_warp.py)
