# LC 1473 — Paint House III
# DP: dp[i][color][k] = min cost after painting i houses, i-1 is color, with k neighborhoods
from typing import List

def minCost(houses: List[int], cost: List[List[int]], m: int, n: int, target: int) -> int:
    INF = 10**15
    # dp_prev[color][k] for processed houses up to previous index
    dp_prev = [[INF]*(target+1) for _ in range(n+1)]  # colors 1..n
    # initialize for house 0
    if houses[0] != 0:
        c = houses[0]
        dp_prev[c][1] = 0
    else:
        for c in range(1, n+1):
            dp_prev[c][1] = cost[0][c-1]
    for i in range(1, m):
        dp_cur = [[INF]*(target+1) for _ in range(n+1)]
        if houses[i] != 0:
            allowed = [houses[i]]
        else:
            allowed = list(range(1, n+1))
        for c in allowed:  # color chosen for house i
            add = 0 if houses[i] == c else (0 if houses[i] != 0 else cost[i][c-1])
            for pc in range(1, n+1):
                for k in range(1, target+1):
                    if dp_prev[pc][k] >= INF:
                        continue
                    if c == pc:
                        # same neighborhood count
                        if dp_prev[pc][k] + add < dp_cur[c][k]:
                            dp_cur[c][k] = dp_prev[pc][k] + add
                    else:
                        if k+1 <= target and dp_prev[pc][k] + add < dp_cur[c][k+1]:
                            dp_cur[c][k+1] = dp_prev[pc][k] + add
        dp_prev = dp_cur
    ans = min(dp_prev[c][target] for c in range(1, n+1))
    return -1 if ans >= INF else ans

if __name__ == "__main__":
    houses = [0,0,0,0,0]
    cost = [[1,10],[10,1],[10,1],[1,10],[5,1]]
    m, n, target = 5, 2, 3
    print(minCost(houses, cost, m, n, target))  # 9
