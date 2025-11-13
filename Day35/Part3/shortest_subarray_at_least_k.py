from collections import deque
from typing import List

def shortest_subarray(nums: List[int], K: int) -> int:
    n = len(nums)
    P = [0] * (n + 1)
    for i in range(n):
        P[i+1] = P[i] + nums[i]
    ans = n + 1
    dq = deque()
    for i in range(n + 1):
        while dq and P[i] - P[dq[0]] >= K:
            ans = min(ans, i - dq.popleft())
        while dq and P[i] <= P[dq[-1]]:
            dq.pop()
        dq.append(i)
    return ans if ans <= n else -1

if __name__ == "__main__":
    print(shortest_subarray([2,-1,2], 3))  # Expected 3
