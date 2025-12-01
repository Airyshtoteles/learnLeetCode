# Part 2: Necromancer’s Minion Network

## Problem Description

The Necromancer needs to connect all his minion outposts into a single communication network to coordinate the attack on the kingdom.

You are given `N` outposts (labeled 0 to N-1) and a list of potential magical ley-lines (edges) that can connect them. Each ley-line has a base mana cost. However, some ley-lines are passing through "Purified Zones" (corrupted for the Necromancer) and require **double** the mana to stabilize.

Find the **minimum total mana cost** required to connect all outposts so that every outpost can communicate with every other outpost (directly or indirectly). If it is impossible to connect all outposts, return `-1`.

### Input Format
1.  `N`: Number of outposts (Integer).
2.  `Connections`: A list of tuples/vectors, where each contains `[u, v, cost, is_corrupted]`.
    *   `u`, `v`: Indices of the outposts.
    *   `cost`: Base mana cost.
    *   `is_corrupted`: Boolean (0 or 1). If 1, the actual cost is `cost * 2`.

### Output Format
*   An integer representing the minimum total mana cost.

### Example

**Input:**
```text
N = 4
Connections = [
  [0, 1, 10, 0],
  [1, 2, 20, 1],
  [2, 3, 30, 0],
  [0, 3, 50, 0],
  [1, 3, 5, 0]
]
```

**Logic:**
*   Edge 0-1: Cost 10 (Normal)
*   Edge 1-2: Cost 20 * 2 = 40 (Corrupted)
*   Edge 2-3: Cost 30 (Normal)
*   Edge 0-3: Cost 50 (Normal)
*   Edge 1-3: Cost 5 (Normal)

Sorted Edges by actual cost:
1.  1-3: 5
2.  0-1: 10
3.  2-3: 30
4.  1-2: 40
5.  0-3: 50

MST Construction:
*   Add 1-3 (Cost 5). Sets: {1,3}, {0}, {2}
*   Add 0-1 (Cost 10). Sets: {0,1,3}, {2}
*   Add 2-3 (Cost 30). Sets: {0,1,2,3} -> All connected.

Total Cost = 5 + 10 + 30 = 45.

**Output:**
```text
45
```
