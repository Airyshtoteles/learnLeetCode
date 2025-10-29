# The Abyssal Sequence
# S[0] = 1; S[i] = S[i-1] * (i ^ S[i-1]) mod MOD, i >= 1
# Goal: compute S[n] for n up to 1e18.
# Note: The recurrence explicitly depends on i and S[i-1], and XOR is not modulo; true period is not guaranteed.
# We'll implement Floyd cycle detection on the sequence of S while tracking i, with a safety cap.
# If a cycle is found (S repeats), we can skip ahead; otherwise we fall back to capped simulation and report inability for huge n.
from typing import Optional, Tuple

MOD = 10**9 + 7

def abyssal_S(n: int, cap: int = 2_000_000) -> Tuple[Optional[int], str]:
    if n == 0:
        return 1, "ok"
    # Floyd cycle-finding on values S only; state progresses by i+=1.
    def next_val(i: int, s: int) -> Tuple[int,int]:
        ns = (s * (i ^ s)) % MOD
        return i+1, ns
    # tortoise and hare
    i1, s1 = 1, (1 * (1 ^ 1)) % MOD  # step once from S0=1
    i2, s2 = 1, s1
    # advance hare one extra
    i2, s2 = next_val(i2, s2)
    steps = 0
    while steps < cap and s1 != s2:
        i1, s1 = next_val(i1, s1)
        i2, s2 = next_val(*next_val(i2, s2))
        steps += 1
    if steps >= cap:
        # no cycle detected within cap
        if n <= cap:
            # simulate directly
            i, s = 0, 1
            while i < n:
                i, s = next_val(i, s)
            return s, "partial"
        return None, "no-cycle"
    # find mu
    mu_i, mu_s = 0, 1
    i_t, s_t = 0, 1
    i_h, s_h = i1, s1
    while s_t != s_h:
        i_t, s_t = next_val(i_t, s_t)
        i_h, s_h = next_val(i_h, s_h)
        mu_i += 1
    # find lambda
    lam = 1
    i_h, s_h = next_val(i_t, s_t)
    while s_h != s_t:
        i_h, s_h = next_val(i_h, s_h)
        lam += 1
    # Now compute S[n]
    if n < mu_i:
        i, s = 0, 1
        while i < n:
            i, s = next_val(i, s)
        return s, "ok"
    # advance to start of cycle, then jump by (n-mu) mod lam
    k = (n - mu_i) % lam
    i, s = 0, 1
    for _ in range(mu_i):
        i, s = next_val(i, s)
    for _ in range(k):
        i, s = next_val(i, s)
    return s, "ok"

if __name__ == "__main__":
    print(abyssal_S(1000)[0])
    # For extremely large n, may return (None, "no-cycle") if no period found within cap.
