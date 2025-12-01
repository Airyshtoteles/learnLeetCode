from typing import List

def max_reward(reward: List[int], require: List[List[int]]) -> int:
    n = len(reward)
    need_mask = [0]*n
    for i in range(n):
        m = 0
        for pre in require[i]:
            m |= 1<<pre
        need_mask[i] = m
    N = 1<<n
    dp = [-10**15]*N
    dp[0] = 0
    ans = 0
    for mask in range(N):
        if dp[mask] < -10**14:
            continue
        ans = max(ans, dp[mask])
        for i in range(n):
            if (mask>>i) & 1:
                continue
            if (mask & need_mask[i]) == need_mask[i]:
                nmask = mask | (1<<i)
                dp[nmask] = max(dp[nmask], dp[mask] + reward[i])
    return ans

if __name__ == "__main__":
    reward = [3,5,2,10]
    require = [[], [0], [0], [1,2]]
    print(max_reward(reward, require))  # Expected 20
