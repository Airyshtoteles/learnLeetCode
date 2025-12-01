# Mirror XOR Transformation

Difficulty: Hard

You are given an integer array `nums` of length `n`. In one operation you choose any subarray `[l,r]` and transform it so each element becomes:
```
nums[i] -> nums[l+r - i] XOR nums[i]
```
for all `i` in `[l,r]`.
Goal: Minimum number of operations to make all elements equal.

## Key Observations
Let the target value after all operations be `X`. Consider choosing a subarray. For a pair of mirrored indices `(a,b)` within `[l,r]` (with `a+b = l+r`):
```
nums[a] -> nums[b] XOR nums[a]
nums[b] -> nums[a] XOR nums[b]
```
Both results are identical: `nums[a] XOR nums[b]`.
Thus one operation can force every mirror pair inside a chosen subarray to become the same XOR of its original pair. If the subarray length is odd, the middle element maps to itself and becomes `nums[mid] XOR nums[mid] = 0`.

### Minimal Operations Criterion
1. If all elements already equal: answer = 0.
2. Else if the array is a palindrome (i.e., `nums[i] == nums[n-1-i]` for all `i`): one operation on the whole array makes every pair become `nums[i] XOR nums[n-1-i] = 0` (or the same value). Answer = 1.
3. Otherwise, we can in two operations:
   - First, apply on one large subarray to equalize many pairs.
   - Second, cover remaining mismatch positions.

This yields an upper bound of 2 and is tight for arrays that are not palindromes and not already uniform.

So the answer is simply:
```
0 if all equal
1 if palindrome
2 otherwise
```

## Complexity
- Time: `O(n)`
- Space: `O(1)`

## Examples
- `[1,3,2,3,1]` is palindrome but not uniform ⇒ 1.
- `[5,5,5]` uniform ⇒ 0.
- `[1,2,3]` not uniform, not palindrome ⇒ 2.
