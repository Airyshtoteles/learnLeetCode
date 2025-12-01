# Day 21 — Part 5: Parallel Courses III (LC 2050)

Approach:
- Build DAG with indegrees, run topological order.
- DP: dist[v] = max over predecessors u of (dist[u] + time[v]). Initialize sources with dist[i]=time[i]. Answer is max dist.

Complexity:
- Time: O(n + m)
- Space: O(n + m)

Files:
- parallel_courses_iii.py — Python topo+DP with example.
- parallel_courses_iii.cpp — C++ topo+DP with example in main().
