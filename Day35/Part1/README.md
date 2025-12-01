# Min Subarray Removal to Make Sum Divisible by p

Difficulty: Hard

Given an array `nums` and integer `p`, remove the smallest-length subarray so that the sum of the remaining elements is divisible by `p`. Return that length, or `-1` if impossible.

This is equivalent to finding the shortest subarray whose sum has remainder `target = total % p` modulo `p`.

## Approach (Prefix Mod + Hash Map)
Let `pref[i]` be prefix sums modulo `p`. We need `pref[j] == (pref[i] - target) mod p` for minimal `i-j`.
We scan once and store the last index for each remainder in a map.

- Time: `O(n)`
- Space: `O(p)` (bounded by `n`)
