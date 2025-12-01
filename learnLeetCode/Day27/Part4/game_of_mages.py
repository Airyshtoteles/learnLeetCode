from functools import lru_cache
from typing import List

def max_power(mana: List[int], power: List[int]) -> int:
    n = len(mana)
    # Precompute removal masks: if we add i, remove any j in S with (power[j]>power[i] and mana[j]<mana[i])
    rem_mask = [0]*n
    for i in range(n):
        mask = 0
        for j in range(n):
            if power[j] > power[i] and mana[j] < mana[i]:
                mask |= (1<<j)
        rem_mask[i] = mask
    sum_power = [0]*(1<<n)
    for s in range(1<<n):
        sp = 0
        for i in range(n):
            if s>>i & 1: sp += power[i]
        sum_power[s]=sp

    @lru_cache(maxsize=None)
    def dfs(S: int) -> int:
        best = sum_power[S]
        # try recruit a new mage i
        for i in range(n):
            if (S>>i) & 1: continue
            S2 = (S & ~rem_mask[i]) | (1<<i)
            if S2 == S:  # adding i removed itself (shouldn't happen), or no change
                continue
            best = max(best, dfs(S2))
        return best

    return dfs(0)

if __name__ == "__main__":
    mana = [3,6,4,5]
    power = [5,3,8,7]
    print(max_power(mana, power))  # Expected 15 under removal-on-add interpretation
