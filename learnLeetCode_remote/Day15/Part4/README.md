# Day 15 — Part 4: Largest Rectangle in Histogram (LC 84)

- Use a monotonic increasing stack; append a trailing 0 to flush remaining bars.
- When a bar is lower than the top, pop and compute area with that height.

Files:
- `largest_rectangle.py`
- `largest_rectangle.cpp`

Try:
```
python largest_rectangle.py
```
