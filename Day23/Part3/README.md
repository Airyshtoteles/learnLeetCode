# Day 23 — Part 3: The Clockwork Cipher

Goal: Minimal number of circular range +1 operations (mod 12) to make all gear values equal.

Approach:
- For a target value t in [0..11], required increments per position are inc[i] = (t − gears[i]) mod 12.
- A circular +1 on [a..b] raises a consecutive block in inc. The minimal number of such operations for a fixed inc sequence equals the sum of positive jumps of inc along some break (rotation) where we take prev = 0 at the start.
- So we take the minimum over all t and all n rotations of sum(max(0, inc[i] − prev)).

Complexity: O(12 · n^2). For small n this is fine; can be optimized with prefix minima if needed.

Files:
- clockwork_cipher.py — Python version.
- clockwork_cipher.cpp — C++17 version with a small main.
