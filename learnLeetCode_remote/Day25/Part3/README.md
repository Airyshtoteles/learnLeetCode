# Day 25 — Part 3: The Mirror Code

Goal: Maximize the longest run of 1s by flipping at most k segments, with a single-step reflective effect: when flipping a segment [L,R], also flip bit L−1 if it’s 0 and equals the left edge (0), and flip bit R+1 if it’s 0 and equals the right edge (0). We assume the reflection doesn’t cascade.

Approach (zero-run window):
- Partition s into zero-runs [L,R]. Flipping a contiguous block of zero-runs (up to k runs) creates a continuous 1-block spanning from the leftmost L to rightmost R, including any 1s between.
- Reflection adds up to +1 on each side if the immediate outside bit is 0.
- Extend further through contiguous 1s outside the span.
- Take the best over all windows of at most k zero-runs.

Complexity: O(n) to build runs + O(m) windows with O(run-adjacent) extensions; worst-case O(n^2) if many tiny runs, acceptable for moderate n.

Files:
- mirror_code.py — Python implementation.
- mirror_code.cpp — C++17 implementation.
