# Glyphcraft — Spellcraft Combination

Level: Hard

Given a lowercase string S (|S| ≤ 2e5) and Q queries. Each query [L,R,X] asks: how many distinct ways to choose k ≥ 1 non-overlapping, ordered segments fully inside S[L..R] such that the union of characters appearing in the chosen segments contains exactly X unique letters. Two ways differ if their sets of segment positions differ. Return answer modulo 1e9+7.

## Notes on Difficulty
Counting over all ordered, non-overlapping segment sets with a constraint on the union of characters is highly non-trivial. A direct DP over (position, inSegment, characterMask) is 2^26 and infeasible. We outline an offline approach:

- Precompute next/prev occurrences for all 26 letters to support fast expansion of unique sets.
- For each query window, compress positions and build an automaton that advances the union-of-letters via extending or closing segments. This enables DP in O(L * B) where B is number of reachable masks in practice (often far below 2^26 on real text).
- We use inclusion–exclusion on letters to count partitions whose union excludes some subset, then invert to obtain exact-X counts. This yields per-query work proportional to 2^X times a fast partition-count function.

This repository includes scaffolding and reference stubs with detailed docstrings for future completion.
