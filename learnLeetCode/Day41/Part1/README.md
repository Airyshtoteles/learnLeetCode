# Time-Warped Subarray Matching

Level: Hard

Given arrays A and B and integer k, determine if there exists a contiguous subarray of A of length |B| that can be transformed into B using at most k time-warp operations. One time-warp operation doubles or halves (integer division by 2, only if even) a single element. Halving must keep the value integer.

## Key Observation
Operations only adjust the power-of-two factor of a number; the odd part (after removing all factors of two) is invariant. Let `odd(x)` be x with all factors of 2 removed, and `exp2(x)` be the number of times 2 divides x.
Element `x` can become `y` iff:
- `x = 0` and `y = 0`, OR
- `odd(x) == odd(y)` (non-zero case).
Minimal operations needed = |exp2(x) - exp2(y)|.
Zero cannot change to non-zero; non-zero cannot become zero.

## Algorithm
1. Precompute `oddA[i], eA[i]` for A and `oddB[j], eB[j]` for B.
2. Build pattern array of odd parts for B.
3. Use KMP / Z algorithm over A's odd parts to find all starts where `oddA[i..i+|B|-1]` equals `oddB[0..|B|-1]`.
4. For each candidate start, accumulate `sum |eA[i+t] - eB[t]|`; if any ≤ k return true.
5. Edge cases: mismatch zeros, lengths.

Complexity: O(n logV + m logV + (n+m)) for preprocessing + pattern search + candidate verification. Worst-case candidate checking O(#matches * m). In practice, #matches small.

## Example
A = [4,3,8,2,16], B=[1,8], k=3
Odd parts A: [1,3,1,1,1], exps: [2,0,3,1,4]
Odd parts B: [1,1], exps: [0,3]
Matches of odd pattern length 2 in A at indices where odd parts are [1,1]: positions 0,2,3.
Costs:
- idx 0: |2-0|+|0-3|=5 >3
- idx 2: |3-0|+|1-3|=5 >3
- idx 3: |1-0|+|4-3|=2 ≤3 → true
