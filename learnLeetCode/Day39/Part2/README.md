# Monster Aggro System

Difficulty: Hard — Priority Queue + Greedy + Math

You have `n` monsters. Each second:
- Every monster's aggro increases by `hate[i]`.
- You may reduce ONE monster's aggro by `X`.
- If any aggro reaches `threshold[i]`, you lose.

Goal: return the minimum `X` so you can survive forever.

## Model and Result
The total aggro increases at rate `Σ hate[i]` per second, while you can remove `X` per second. For indefinite survival, a necessary condition is `X ≥ Σ hate[i]` (otherwise total aggro diverges). This condition is also sufficient with an appropriate scheduling (always reduce the monster with smallest remaining margin to threshold).

Therefore the minimal `X` is:

```
X* = max( max(hate), Σ hate[i] )
```

- `max(hate)` ensures you can keep up with the fastest-increasing monster when it is served every second if needed.
- `Σ hate[i]` ensures the total does not diverge.

This `X*` is computed in `O(n)` time.

Note: If your sample expects a value lower than `Σ hate[i]`, that scenario cannot be sustained forever; the total aggro will diverge.
