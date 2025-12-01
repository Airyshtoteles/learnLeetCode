# Tower Defense — Minimum Upgrade Cost

Difficulty: Hard — Segment Thinking

You have `n` positions with enemy HP `HP[i]`. One "upgrade shot" selects a range `[L, R]`, costs `(R-L+1)`, and reduces each HP in that range by `D`. Repeat any number of times. Minimize total cost so that all HP become `≤ 0`.

## Key Observation
Let `A[i] = ceil(HP[i] / D)` be the number of unit decrements needed at position `i`. Each shot of any range contributes `1` decrement to every cell in that range; the total cost of a shot equals the number of positions it contributes to. Therefore, summing over all shots, the total cost equals the sum of how many decrements each position receives.

To finish, position `i` must receive at least `A[i]` decrements. Hence any feasible plan has cost ≥ `Σ A[i]`, and using single-cell shots at each `i` exactly `A[i]` times achieves this bound. Thus the minimum total cost is:

```
answer = Σ ceil(HP[i] / D)
```

- Time: `O(n)`
- Space: `O(1)` extra
