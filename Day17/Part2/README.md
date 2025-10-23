# Day 17 — Part 2: Maximum Number of Robots Within Budget (LC 2390)

Approach:
- Sliding window two pointers.
- Maintain a deque (monotonic decreasing) of indices to get max chargeTime in window.
- Keep running sum of runningCosts in window.
- While maxCharge + window_size * sumRunning > budget, shrink left.

Files:
- `max_robots.py`
- `max_robots.cpp`

Try:
```
python max_robots.py
```
