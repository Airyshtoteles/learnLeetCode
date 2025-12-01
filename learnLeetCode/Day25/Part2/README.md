# Day 25 — Part 2: The Chrono Keys

Model:
- Portals form a functional graph: each floor i has at most one outgoing edge to portal[i] (or -1 to stop).
- On visiting floor i, time increases by timeShift[i] (including at the last floor).

Goal: Start at floor 0 with time=0 and determine if some walk along portals reaches floor n−1 with time exactly target.

Approach:
- Follow portals from 0, tracking the first time we visit each floor (Floyd/Kahn unnecessary since it’s a functional graph).
- If we reach n−1 before any cycle, we check time exactly.
- If we encounter a cycle, let C be the sum of timeShift along the cycle. If n−1 lies on the cycle, the times when we land on n−1 form an arithmetic progression b + k·C (k≥0). Check if target matches.
- Otherwise, n−1 is unreachable (once in a cycle you can’t leave a functional graph), return false.

Edge cases:
- If C==0 and n−1 in the cycle, only the first arrival time b is achievable.
- If the walk hits -1 (no portal), we stop.

Files:
- chrono_keys.py — Python implementation with the sample.
- chrono_keys.cpp — C++17 implementation.
