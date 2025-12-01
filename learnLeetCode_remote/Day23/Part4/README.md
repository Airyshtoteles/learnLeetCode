# Day 23 — Part 4: The Abyssal Sequence

Definition: S[0] = 1; for i ≥ 1, S[i] = S[i−1] · (i XOR S[i−1]) mod 1e9+7.

Challenge: n can be as large as 1e18. Since the recurrence depends explicitly on i and XOR, a true period is not guaranteed. We therefore:

Approach:
- Use Floyd’s cycle detection on the sequence of S-values while stepping i.
- If a cycle is detected with pre-period μ and period λ, compute S[n] by simulating μ steps and then (n−μ) mod λ steps.
- If no cycle is found within a cap (default 2e6 steps), we can still return S[n] if n ≤ cap by direct simulation; otherwise report that no cycle was found within the cap.

Notes:
- This strategy is practical if a short period exists (as often happens in XOR-based sequences). If the sequence is aperiodic (or has a massive period), exact evaluation for n≈1e18 is infeasible without additional structure.

Files:
- abyssal_sequence.py — Python version with Floyd and a safety cap.
- abyssal_sequence.cpp — C++17 version using 128-bit intermediate to avoid overflow.
