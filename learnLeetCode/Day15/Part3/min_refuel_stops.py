import heapq
from typing import List

# LeetCode 871 — Minimum Number of Refueling Stops
# Greedy with max-heap of fuel from stations we've passed.

def minRefuelStops(target: int, startFuel: int, stations: List[List[int]]) -> int:
    fuel = startFuel
    ans = 0
    i = 0
    n = len(stations)
    maxheap = []  # store negative for max-heap behavior via heapq
    while fuel < target:
        # push all stations within current reach
        while i < n and stations[i][0] <= fuel:
            heapq.heappush(maxheap, -stations[i][1])
            i += 1
        if not maxheap:
            return -1
        fuel += -heapq.heappop(maxheap)
        ans += 1
    return ans

if __name__ == "__main__":
    print(minRefuelStops(100, 10, [[10,60],[20,30],[30,30],[60,40]]))  # 2
