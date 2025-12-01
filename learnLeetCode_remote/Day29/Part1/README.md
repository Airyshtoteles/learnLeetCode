# Battle Arena: Energy Redistribution

You have n players with initial energies `energy[i]`. In one move, pick players i and j and transfer 1 unit from i to j (only if `energy[i] > 0`). Make all energies equal in the minimum number of moves, or return -1 if impossible.

## Observations
- Total energy is invariant. Let `S = sum(energy)` and `avg = S / n`.
- Necessary and sufficient: `S % n == 0`. Otherwise impossible.
- Every move transfers exactly 1 unit from a surplus to a deficit position.
- The minimal number of unit transfers equals the total surplus: `ans = sum(max(0, energy[i] - avg))`.

Note: Some formulations report `sum |energy[i] - avg|` as the total imbalance (which is exactly `2*ans`). Here we return the number of transfers (unit moves), i.e., `ans`.

## Files
- `energy_redistribution.py` — O(n) solution
- `energy_redistribution.cpp` — C++17 implementation
