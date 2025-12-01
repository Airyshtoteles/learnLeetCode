# Infinite Jump Game With Multi-State Tiles

Level: Hard

Array A length n, start at index 0 target n-1. At position pos you may jump to pos + A[pos] or pos - A[pos] (if in range). After landing on index i, A[i] increases by 1 (up to at most original + c). After it has been increased c times (i.e. visited c additional times), it locks to 0 (no further jumps possible from it).

Decide if target index n-1 is reachable.

## Modeling
We simulate BFS over state (pos, visits[i] counts implicit via current dynamic A). Instead of storing full vector, we keep current A array mutated in-place with backtracking not required because BFS explores non-decreasing modifications; once we increment a tile its future value only larger (or eventually 0 after cap) which only changes jump distance for future visits.

We maintain for each position the maximum times we have visited (up to c+1) and avoid reprocessing if visiting again would not yield a new jump length. For each pos we may have up to c+1 distinct jump lengths (original, original+1, ..., original+c) then 0.

If during exploration we reach n-1 return True. If BFS exhausts states return False.

## Complexity
Worst-case O(n * min(c+1, n)) expansions. Practical pruning with visited counts.
