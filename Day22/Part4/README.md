# Day 22 — Part 4: Minimum Incompatibility (LC 1681)

Goal: Partition `nums` into `k` groups of equal size `n/k` (no duplicates within any group) to minimize the sum over groups of `(max - min)`.

Approach:
- Early check: if any value appears more than `k` times, it's impossible → return `-1`.
- Precompute all valid subsets of indices of size `n/k` that contain unique values and record their incompatibility `max - min`.
- Bitmask DP: `dp[mask] =` min total incompatibility using the set of indices in `mask`.
  - Expand by picking the first unused index `i` and trying all valid subsets `sub` of remaining indices that include `i`.

Complexity:
- Precompute: O(C(n, n/k) · n) with `n ≤ 16`.
- DP: O(2^n · C(n, n/k)) in practice fast for constraints.

Files:
- minimum_incompatibility.py — Python DP with bitmask and subset precomputation.
- minimum_incompatibility.cpp — C++ version with the same logic and small `main()` demos.
