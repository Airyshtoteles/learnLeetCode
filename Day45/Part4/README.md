# Day 45 Part 4: Spell Deck Optimization

## Problem Description

You have a deck of $N$ spells. Each spell $i$ has:
*   `power[i]`: Damage dealt.
*   `cooldown[i]`: Time taken to cast (or recover).
*   `buffTag[i]`: A string or ID representing the spell's type.

**Mechanic:**
*   If you cast Spell A then Spell B, and `buffTag[A] == buffTag[B]`, then Spell B deals **double damage** ($2 \times power[B]$).
*   Spells can be used infinitely.
*   **Goal:** Minimize total time (sum of cooldowns) to deal at least $H$ damage to a boss.

## Algorithm: Unbounded Knapsack / Shortest Path on DAG

This problem is equivalent to finding the minimum cost (time) to reach a target value (damage $H$), where the "value" of an item (spell) depends on the previous item.

### State
`dp[h][last_tag]` = Minimum time to deal exactly (or at least) $h$ damage, given the last spell had `last_tag`.
*   $h$: Current damage dealt ($0 \dots H$).
*   $last\_tag$: The tag of the last spell used ($0 \dots T$, where $T$ is number of unique tags). Use a special value for "None" (start).

### Transitions
From state `dp[h][prev_tag]`, try all spells $i$:
*   `current_tag = buffTag[i]`
*   `damage = power[i]`
*   If `current_tag == prev_tag`: `damage *= 2`
*   `next_h = min(H, h + damage)`
*   `cost = cooldown[i]`
*   Update: `dp[next_h][current_tag] = min(dp[next_h][current_tag], dp[h][prev_tag] + cost)`

### Optimization
Since we want min cost for target value, this is like Dijkstra on a graph where nodes are `(damage, last_tag)`.
*   Nodes: $H \times (T+1)$.
*   Edges: $N$ outgoing edges from each node.
*   Complexity: $O(H \cdot T \cdot N)$.
*   If $H$ is large, this is slow. But usually "Boss HP" in such DP problems is $\le 10^4$ or $10^5$. If $H$ is huge ($10^9$), we'd need matrix exponentiation or cycle finding (max mean cycle), but "Hard" usually implies standard DP or Dijkstra. I'll assume $H \le 10000$.

## Implementation Details
*   Map tags to integers $0 \dots T-1$.
*   Use `dist[damage][tag]` array initialized to Infinity.
*   Priority Queue for Dijkstra: `(time, damage, last_tag)`.
    *   Note: Since we want to reach *at least* $H$, we can cap damage at $H$.
    *   However, Dijkstra usually explores from 0 upwards.
    *   State: `(current_damage, last_tag)`.
    *   Priority: `current_time`.
