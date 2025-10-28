# Day 22 — Part 3: Parallel Courses III (LC 2050)

Approach:
- Build DAG from relations; indegree per node.
- Topological order with queue; maintain dist[v] = max completion time to finish v.
- Answer is max dist.

Complexity:
- Time: O(n + m)
- Space: O(n + m)

Files:
- parallel_courses_iii.py — Python topo + DP with example.
- parallel_courses_iii.cpp — C++ topo + DP with example in main().
