# The Oracle Stones

You have n stones in a circle with magic values a[i]. Operation: pick adjacent stones (i, j) and replace them with one stone whose value is `a[i] XOR a[j]`. Repeat until one stone remains. Find the minimum possible final value.

## Key Insight (Invariance)
The XOR of all stones is invariant under the operation:
- Let S be the multiset XOR of all stones.
- Replacing `a` and `b` by `a XOR b` changes the total XOR from `S = rest XOR a XOR b` to `S' = rest XOR (a XOR b)` which equals S.
- Therefore the final single value must equal the XOR of the initial array, regardless of the order of merges.

Hence the answer is simply `a[0] XOR a[1] XOR ... XOR a[n-1]`.

For the example `a = [1,3,5,7]`, the XOR is `1^3^5^7 = 0`, which matches the expected output `0`.

## Files
- `oracle_stones.py` — Computes XOR of the array
- `oracle_stones.cpp` — C++ equivalent
