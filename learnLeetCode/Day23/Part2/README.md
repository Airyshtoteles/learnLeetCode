# Day 23 — Part 2: The Temple of Shadows

Goal: Light the minimum number of rooms so every directed cycle has non-negative total darkness.

Assumption: Lighting a room sets its darkness to 0.

Approach:
- Decompose graph into SCCs (Kosaraju/Tarjan). Only SCCs that contain a cycle matter (size>1 or a self-loop).
- For each such SCC, let S be the sum of darkness values.
  - If S ≥ 0, no lantern needed in that SCC.
  - Else, sort negative values ascending and light the most negative rooms until the new sum ≥ 0.
- Sum counts across SCCs.

Correctness intuition: Any directed cycle is wholly contained in some SCC. Neutralizing the most negative nodes minimizes the number needed to raise all cycle sums to non-negative.

Complexity: O(n + m) for SCC, plus O(s log s) per SCC for sorting negatives (s = nodes in that SCC).

Files:
- temple_of_shadows.py — Python implementation with a sample.
- temple_of_shadows.cpp — C++17 implementation with the same logic.
