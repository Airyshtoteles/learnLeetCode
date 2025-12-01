# Recursive Clock Synchronization

You have n clocks with values 0..11 and m buttons. Pressing button i advances some clocks by +1 (mod 12) based on ops[i][j] ∈ {0,1}. Find the minimum total presses to make all clocks 0, or -1 if impossible.

## Approach (Recursive Search 0..11 per Button)
- Pressing a button 12 times is a no-op, so each button’s press count is in [0..11].
- We try counts for button 0..m-1 recursively, applying effects incrementally to the working clock vector.
- Prune branches whose partial press sum already ≥ best.
- At the end, if all clocks are 0, update `best`.

This is exponential in m (12^m), but works for modest m and matches the problem’s backtracking spirit.

## Files
- `clock_sync.py` — Python recursive DFS with pruning
- `clock_sync.cpp` — C++17 equivalent
