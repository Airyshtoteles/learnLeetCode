# Day 15 — Part 1: Minimum Number of Days to Eat N Oranges (LC 1553)

Key recurrence with memoization:

- f(0) = 0, f(1) = 1
- f(n) = 1 + min( n % 2 + f(n/2), n % 3 + f(n/3) )

Explanation: spend `n%2` days eating one per day to make divisible by 2, then one more day to eat `n/2` at once; similarly for 3.

Files:
- `min_days_oranges.py`
- `min_days_oranges.cpp`

Try:
```
python min_days_oranges.py
```
