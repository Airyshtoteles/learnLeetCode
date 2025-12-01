from typing import List
import heapq
from collections import defaultdict

class DualHeap:
    def __init__(self, k: int):
        self.small = []  # max-heap (store negatives)
        self.large = []  # min-heap
        self.del_small = defaultdict(int)
        self.del_large = defaultdict(int)
        self.k = k
        self.small_size = 0
        self.large_size = 0

    def prune(self, heap, delayed):
        while heap:
            x = heap[0]
            val = -x if heap is self.small else x
            if delayed[val] > 0:
                heapq.heappop(heap)
                delayed[val] -= 1
            else:
                break

    def rebalance(self):
        # maintain small_size == large_size or small_size == large_size + 1
        if self.small_size > self.large_size + 1:
            x = -heapq.heappop(self.small)
            self.small_size -= 1
            heapq.heappush(self.large, x)
            self.large_size += 1
            self.prune(self.small, self.del_small)
        elif self.small_size < self.large_size:
            x = heapq.heappop(self.large)
            self.large_size -= 1
            heapq.heappush(self.small, -x)
            self.small_size += 1
            self.prune(self.large, self.del_large)

    def insert(self, x: int):
        if not self.small or x <= -self.small[0]:
            heapq.heappush(self.small, -x)
            self.small_size += 1
        else:
            heapq.heappush(self.large, x)
            self.large_size += 1
        self.rebalance()

    def erase(self, x: int):
        # lazy delete from appropriate heap
        if self.small and x <= -self.small[0]:
            self.del_small[x] += 1
            self.small_size -= 1
            if self.small and -self.small[0] == x:
                self.prune(self.small, self.del_small)
        else:
            self.del_large[x] += 1
            self.large_size -= 1
            if self.large and self.large[0] == x:
                self.prune(self.large, self.del_large)
        self.rebalance()

    def median(self) -> float:
        if self.k % 2 == 1:
            return float(-self.small[0])
        else:
            return (-self.small[0] + self.large[0]) / 2.0

def medianSlidingWindow(nums: List[int], k: int) -> List[float]:
    dh = DualHeap(k)
    res: List[float] = []
    for i, x in enumerate(nums):
        dh.insert(x)
        if i >= k:
            dh.erase(nums[i - k])
        if i >= k - 1:
            res.append(dh.median())
    return res

if __name__ == "__main__":
    print(medianSlidingWindow([1,3,-1,-3,5,3,6,7], 3))
