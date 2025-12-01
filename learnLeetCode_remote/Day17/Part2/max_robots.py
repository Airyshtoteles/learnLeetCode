from collections import deque
from typing import List

# LC 2390 — Maximum Number of Robots Within Budget
# Maintain sliding window with monotonic deque for max(chargeTimes) and running sum of runningCosts.

def maximumRobots(chargeTimes: List[int], runningCosts: List[int], budget: int) -> int:
    n = len(chargeTimes)
    dq = deque()  # indices with decreasing chargeTimes
    left = 0
    total_run = 0
    best = 0
    for right in range(n):
        # add right
        total_run += runningCosts[right]
        while dq and chargeTimes[dq[-1]] <= chargeTimes[right]:
            dq.pop()
        dq.append(right)

        # shrink while budget exceeded
        while left <= right and chargeTimes[dq[0]] + (right - left + 1) * total_run > budget:
            if dq and dq[0] == left:
                dq.popleft()
            total_run -= runningCosts[left]
            left += 1
        best = max(best, right - left + 1)
    return best

if __name__ == "__main__":
    print(maximumRobots([3,6,1,3,4], [2,1,3,4,5], 25))  # Expected 3
