# Day 74: Advanced Simulation & Optimization

Today's challenges focus on complex state simulations, interval scheduling, and dynamic programming for compression.

## Part 1: Mana Overflow Cascade
**Problem:** Simulate mana gain with an overflow mechanic where mana halves if it exceeds a limit.
- **Input:** Gain array, Max Mana `M`, Limit `B`.
- **Logic:** Direct simulation. If `M > B`, `M = floor(M/2)`. Check if `M` drops to 0.
- **Solution:** [C++](./Part1/mana_overflow.cpp) | [Python](./Part1/mana_overflow.py)

## Part 2: Platform Swap Puzzle
**Problem:** Determine if platforms can be rearranged such that adjacent height difference is $\le 1$.
- **Input:** Heights `h[]`.
- **Logic:** Sort the array. If the sorted array has any adjacent difference $> 1$, then no permutation can satisfy the condition (since sorting minimizes adjacent differences).
- **Solution:** [C++](./Part2/platform_swap.cpp) | [Python](./Part2/platform_swap.py)

## Part 3: Enemy Aggro Window
**Problem:** Maximize non-overlapping enemy encounters.
- **Input:** Start times `t[]`, Durations `d[]`.
- **Logic:** Interval Scheduling (Greedy). Sort by end time ($t[i] + d[i]$). Always pick the next available interval that finishes earliest.
- **Solution:** [C++](./Part3/enemy_aggro.cpp) | [Python](./Part3/enemy_aggro.py)

## Part 4: Skill Refund Loop
**Problem:** Reach the last index using jumps $i \to i+1$ or $i \to i+c[i]$, constrained by mana refund logic.
- **Input:** Costs `c[]`.
- **Logic:** BFS Reachability. The mana constraint (start 0, refund $c[i]\%2$) implies we can only traverse nodes where $c[i]$ is odd (net cost 0) to maintain non-negative mana. Even costs would reduce mana below 0.
- **Solution:** [C++](./Part4/skill_refund.cpp) | [Python](./Part4/skill_refund.py)

## Part 5: Boss HP Partition
**Problem:** Determine if any subset of damage values sums to a divisor of the Boss HP.
- **Input:** Damages `d[]`, HP `H`.
- **Logic:** Subset Sum problem. Generate all reachable subset sums using a Set (or DP/Bitset). Check if any reachable sum $S > 0$ satisfies $H \% S == 0$.
- **Solution:** [C++](./Part5/boss_partition.cpp) | [Python](./Part5/boss_partition.py)

## Part 6: Replay Compression Score
**Problem:** Maximize compression score (removed characters) by merging adjacent identical substrings.
- **Input:** String `s`.
- **Logic:** Interval DP. Calculate `min_len[i][j]` for substring `s[i..j]`.
    - Split: `min_len[i][j] = min(min_len[i][k] + min_len[k+1][j])`
    - Compress: If `s[i..j]` is periodic with period `L`, `min_len[i][j] = min(min_len[i][j], min_len[i][i+L-1])`.
    - Score = `Length - min_len[0][n-1]`.
- **Solution:** [C++](./Part6/replay_compression.cpp) | [Python](./Part6/replay_compression.py)
