# K-Alternating Subsequence XOR

Difficulty: Hard

Given an array `nums` and integer `k`, choose a subsequence where any two consecutive chosen indices differ by at least `k`. Maximize the XOR of chosen elements.

Example
```
Input: nums = [3,10,5,25,2,8], k = 2
Output: 26
```

## Approach (Linear Basis DP)
Let `S(i)` be the set of achievable XOR values using indices in `[i..n-1]` under the spacing rule (if you pick `i`, you must jump to `i+k`). Then:
```
S(i) = S(i+1)  ∪  (nums[i] XOR S(i+k))
```
The closure of a set under XOR is captured by a binary linear basis. Hence we store for each i a linear basis `B[i]` representing `span(S(i))`. We build from right to left:
```
B[i] = span( B[i+1] ∪ B[i+k] ∪ { nums[i] } )
```
The answer is the maximum value representable by basis `B[0]`.

- Basis insertion is `O(B)` where `B ≈ 31` (bit-width).
- Per index, we insert up to ~`B + 1` vectors, giving `O(B^2)` per i (≈1e3 ops).
- For `n ≤ 1e5` this is feasible in C++. Python version is optimized but may be slower on worst cases.

## Complexity
- Time: `O(n * B^2)` where `B` is bit-width (≤ 31 for 32-bit ints)
- Space: `O(n * B)` to store bases
