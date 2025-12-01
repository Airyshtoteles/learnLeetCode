# Day 31 — Part 4: Bitmask Quest

You have n quests with rewards reward[i] and prerequisites require[i] (list of indices). Complete quests respecting prerequisites to maximize total reward.

Approach:
- State mask indicates completed quests. dp[mask] = max reward achievable.
- Transition: for each quest i not in mask, it's allowed if all requires[i] bits are set in mask. Then dp[mask | (1<<i)] = max(dp[mask | (1<<i)], dp[mask] + reward[i]).
- Answer: max over all masks.

Complexity: O(n * 2^n + total prerequisites checks). n ≤ ~20 is fine.

Files:
- bitmask_quest.py — Python DP over subsets.
- bitmask_quest.cpp — C++17 DP over subsets.
