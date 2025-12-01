# Subtree XOR Magic

Given a tree with node values `val[i]`, you may remove at most one edge to split it into two parts. Define the magic score as XOR(subtree1) ⊕ XOR(subtree2). Find the minimum possible magic score.

## Key Insight (Invariance)
Let `T = XOR of all nodes`. If you cut an edge, you get two parts with XORs `x` and `T ⊕ x`, so the score is `x ⊕ (T ⊕ x) = T`. This is independent of which edge you cut. Therefore, the minimum possible score equals `T` (and is also achieved by any cut that yields two non-empty parts). If you choose not to cut, the problem statement implies two parts are required; we assume a cut is made or that the intended result remains `T`.

## Files
- `subtree_xor_magic.py` — returns XOR of the entire array
- `subtree_xor_magic.cpp` — C++17 version
