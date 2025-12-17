# Day 67: Game Mechanics & Optimization

## Part 1: HP Redistribution Arena
**Problem:** Determine if HP can be equalized by transferring half HP from one unit to another.
**Solution:** Check if total HP is divisible by N.
**Files:** `Part1/hp_redistribution.cpp`, `Part1/hp_redistribution.py`

## Part 2: Procedural Enemy Spawn
**Problem:** Minimize skipped enemies where "Elite" enemies (strictly greater than all previous) force a skip of the next enemy.
**Solution:** Iterate through spawn list. If current is Elite, increment skip count and force skip of next index.
**Files:** `Part2/enemy_spawn.cpp`, `Part2/enemy_spawn.py`

## Part 3: Buff Duration Collapse
**Problem:** Maximize total duration where buffs of same power collapse to the one with max duration.
**Solution:** Sum of max durations for each unique power.
**Files:** `Part3/buff_collapse.cpp`, `Part3/buff_collapse.py`

## Part 4: Dungeon Key Reuse
**Problem:** Navigate grid with reusable key that breaks for 1 step after use.
**Solution:** BFS with state `(row, col, cooldown)`.
**Files:** `Part4/dungeon_key.cpp`, `Part4/dungeon_key.py`

## Part 5: Time Freeze Combo
**Problem:** Minimize steps to delete string given "XYZ" triggers free delete.
**Solution:** If "XYZ" exists, we can reduce string to 2 chars (using the combo recursively). Else length of string.
**Files:** `Part5/time_freeze.cpp`, `Part5/time_freeze.py`

## Part 6: Skill Cooldown Alignment
**Problem:** Find first time `t` where all skills with cooldowns `c[i]` are active.
**Solution:** Least Common Multiple (LCM) of all cooldowns.
**Files:** `Part6/skill_alignment.cpp`, `Part6/skill_alignment.py`
