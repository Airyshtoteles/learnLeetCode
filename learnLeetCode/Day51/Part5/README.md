# Day 51 Part 5: Relic Arena

## Problem Description
In the Relic Arena, ancient artifacts appear at specific time intervals.
You are a relic hunter. You want to collect as many valuable relics as possible.

There are $N$ relics. Each relic $i$ is available during the time interval $[start_i, end_i]$ and has a value $V_i$.
To collect a relic, you must be present for the entire duration.
You cannot collect two relics that overlap in time.
Additionally, after collecting a relic $i$, you need a **cooldown time** of $K$ units to recharge before you can start collecting the next one.
This means if you collect relic $i$, the next relic $j$ must satisfy $start_j \ge end_i + K$.

Maximize the total value of collected relics.

## Input Format
- `relics`: List of tuples `(start, end, value)`.
- `K`: Cooldown time (integer).

## Constraints
- $N \le 10^5$
- $0 \le start_i < end_i \le 10^9$
- $V_i > 0$
- $K \ge 0$

## Strategy
This is a variation of the **Weighted Interval Scheduling** problem.
We can solve it using **Dynamic Programming** with **Binary Search**.

1. Sort the relics by their **end times**.
2. Define $DP[i]$ as the max value obtainable using a subset of the first $i$ relics (in sorted order).
3. For the $i$-th relic (1-based index):
   - Option 1: Don't collect it. Value is $DP[i-1]$.
   - Option 2: Collect it. Value is $V_i + DP[p]$, where $p$ is the index of the last relic that finishes before $start_i - K$.
     - That is, $end_p \le start_i - K$.
     - We can find $p$ using **Binary Search** (specifically `bisect_right` on end times).
4. $DP[i] = \max(DP[i-1], V_i + DP[p])$.
5. Base case: $DP[0] = 0$.

## Complexity
- Sorting: $O(N \log N)$.
- DP Loop: $N$ iterations.
- Binary Search inside loop: $O(\log N)$.
- Total Time: $O(N \log N)$.
- Space: $O(N)$.

