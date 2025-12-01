# Day 15 — Part 3: Minimum Number of Refueling Stops (LC 871)

Greedy strategy:
- Maintain a max-heap of gas from stations you’ve passed but not used.
- While you can reach new stations, add their fuel to the heap.
- When you can’t progress, refuel using the largest available in the heap.

Files:
- `min_refuel_stops.py`
- `min_refuel_stops.cpp`

Try:
```
python min_refuel_stops.py
```
