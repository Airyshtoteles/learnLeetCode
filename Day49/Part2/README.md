# Day 49 Part 2: Arcane Fusion Battle

## Problem Description
In the Arcane Fusion Battle, you possess a collection of **Arcane Cores**, each radiating a specific magical frequency represented by an integer. You can fuse any number of these cores together. The fusion process follows the laws of **XOR** (exclusive OR).

Your goal is to create the ultimate weapon by fusing a subset of cores such that the resulting frequency is maximized.

Given an array of integers `nums` representing the frequencies of the cores, return the **maximum possible XOR sum** of any subset of them.

## Example
**Input:**
```
nums = [3, 10, 5, 25, 2, 8]
```

**Output:**
```
28
```

**Explanation:**
- 5 XOR 25 = 28.
- Or 3 XOR 10 XOR 5 XOR 25 ... let's check.
- 25 (11001)
- 5 (00101)
- 25 ^ 5 = 28 (11100) -> 28.
- Can we get higher?
- Max bits is around 25 (11001).
- Let's try to construct the basis.

## Approach: Linear Basis (Gaussian Elimination)
To maximize the XOR sum, we can use the concept of a **Linear Basis**.
1. We maintain a basis array `basis` where `basis[i]` stores a number that has its highest set bit at position `i`.
2. For each number in `nums`, we try to insert it into the basis.
   - Iterate from the most significant bit (e.g., 60 down to 0).
   - If the number has bit `i` set:
     - If `basis[i]` is 0, we set `basis[i] = number` and break (successfully inserted).
     - If `basis[i]` is not 0, we XOR the number with `basis[i]` to eliminate that bit and continue.
3. Once the basis is built, we construct the maximum result.
   - Initialize `max_xor = 0`.
   - Iterate from the most significant bit down to 0.
   - If `max_xor ^ basis[i] > max_xor`, update `max_xor = max_xor ^ basis[i]`.

## Complexity
- **Time Complexity:** O(N * log(MaxVal)), where N is the number of elements and MaxVal is the maximum possible value (approx 60 iterations for 64-bit integers).
- **Space Complexity:** O(log(MaxVal)) to store the basis.
