# Day 49 Part 4: Rune Compression Arena

## Problem Description
You possess a string of runes `s` and a magical eraser that can remove at most `k` runes.
You want to compress the string using Run-Length Encoding (RLE).
RLE format: "a3b2" for "aaabb".
- If a character appears once, it is just the character ("a").
- If it appears `c` times (`c > 1`), it is the character followed by the count.

Return the **minimum length** of the run-length encoded version of `s` after deleting at most `k` characters.

## Example
**Input:**
```
s = "aaabcccd"
k = 2
```
**Output:**
```
4
```
**Explanation:**
Delete 'b' and 'd'. String becomes "aaaccc".
RLE: "a3c3". Length 4.

## Approach: Dynamic Programming
We use DP with memoization.
`dp(index, k)`: Minimum length of compressed string for suffix `s[index:]` with `k` deletions allowed.

However, simply knowing `index` and `k` isn't enough because the cost of the *next* group depends on whether it merges with the *previous* group.
Wait, the standard approach for this specific problem (LeetCode 1531) usually involves iterating through the *next* group of identical characters.

**Correct DP State:**
Actually, the "iterate forward" approach implicitly handles the merging.
`dp[i][k]` = min length for `s[i:]` with `k` deletions.
Transitions:
1. **Delete `s[i]`**: `dp[i+1][k-1]` (if `k > 0`).
2. **Keep `s[i]`**: We try to extend the run of `s[i]` as far as possible.
   - Iterate `j` from `i` to `n`.
   - Count occurrences of `s[i]` in `s[i...j]`. Let this be `same`.
   - Count characters different from `s[i]` in `s[i...j]`. Let this be `diff`.
   - If `diff > k`, break (cannot delete all intermediate chars).
   - Cost = `length_of_run(same) + dp[j+1][k - diff]`.
   - `length_of_run(c)`:
     - 1 if c=1
     - 2 if c=2..9
     - 3 if c=10..99
     - 4 if c=100

## Complexity
- **Time:** O(N^2 * K). With N=100, K=100, this is 10^6 operations. Feasible.
- **Space:** O(N * K).
