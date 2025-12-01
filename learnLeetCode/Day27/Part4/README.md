# Game of Mages

You have n mages with `mana[i]` and `power[i]`. You recruit mages one by one. When you recruit mage `i`, any mage `j` with `power[j] > power[i]` and `mana[j] < mana[i]` becomes an enemy (cannot be recruited later). If such a mage `j` is already on your team, they are removed (you cannot keep both), i.e., the team after recruiting `i` cannot contain any `j` with the above relation. Maximize the total power of the final team.

This interpretation matches the sample where recruiting order matters and selecting `(7, then 8)` yields total 15, while trying to add a later high-mana low-power can force removals.

## Approach (Bitmask DP over sets with removal on add)
State `S` = set of currently recruited mages (bitmask). Transition by choosing a new mage `i ∉ S`:
- Remove from `S` any `j ∈ S` s.t. `power[j] > power[i]` and `mana[j] < mana[i]`
- Add `i`
- Recurse with memoization: `f(S) = max( sumPower(S), max_i f(S') )`

This explores all orders, applying removals when conflicts arise. Complexity `O(n * 2^n)`.

## Files
- `game_of_mages.py` — Python DP with memo and example
- `game_of_mages.cpp` — C++17 DP with memo
