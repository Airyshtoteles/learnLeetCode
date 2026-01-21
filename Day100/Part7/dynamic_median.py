import sys
import heapq

# Problem 7: Dynamic Median using Two Heaps (Lazy Removal)
# Python heapq is Min-Heap.
# Lower: Max-Heap (simulate with negated values).
# Upper: Min-Heap.

class DynamicMedian:
    def __init__(self):
        self.lower = [] # Max heap (negated)
        self.upper = [] # Min heap
        self.deleted_lower = {}
        self.deleted_upper = {}
        self.cnt_lower = 0
        self.cnt_upper = 0
        
    def _clean(self):
        while self.lower and self.deleted_lower.get(-self.lower[0], 0) > 0:
            val = -heapq.heappop(self.lower)
            self.deleted_lower[val] -= 1
            
        while self.upper and self.deleted_upper.get(self.upper[0], 0) > 0:
            val = heapq.heappop(self.upper)
            self.deleted_upper[val] -= 1
            
    def _balance(self):
        self._clean()
        
        while self.cnt_lower > self.cnt_upper + 1:
            val = -heapq.heappop(self.lower)
            self.cnt_lower -= 1
            heapq.heappush(self.upper, val)
            self.cnt_upper += 1
            self._clean()
            
        while self.cnt_upper > self.cnt_lower:
            val = heapq.heappop(self.upper)
            self.cnt_upper -= 1
            heapq.heappush(self.lower, -val)
            self.cnt_lower += 1
            self._clean()
            
    def add(self, x):
        self._clean()
        if not self.lower:
            heapq.heappush(self.lower, -x)
            self.cnt_lower += 1
        else:
            top_lower = -self.lower[0]
            if x <= top_lower:
                heapq.heappush(self.lower, -x)
                self.cnt_lower += 1
            else:
                heapq.heappush(self.upper, x)
                self.cnt_upper += 1
        
        self._balance()
        
    def remove(self, x):
        self._clean()
        if self.cnt_lower == 0 and self.cnt_upper == 0:
            return

        top_lower = -self.lower[0]
        
        if x <= top_lower:
            self.deleted_lower[x] = self.deleted_lower.get(x, 0) + 1
            self.cnt_lower -= 1
        else:
            self.deleted_upper[x] = self.deleted_upper.get(x, 0) + 1
            self.cnt_upper -= 1
            
        self._balance()
        
    def get_median(self):
        self._clean()
        if self.cnt_lower == 0:
            return 0
        
        if self.cnt_lower > self.cnt_upper:
            return float(-self.lower[0])
        else:
            return (-self.lower[0] + self.upper[0]) / 2.0

def solve():
    input_data = sys.stdin.read().split()
    if not input_data: return
    iterator = iter(input_data)
    
    try:
        Q = int(next(iterator))
        dm = DynamicMedian()
        results = []
        
        for _ in range(Q):
            type = next(iterator)
            if type == "add":
                x = int(next(iterator))
                dm.add(x)
            elif type == "remove":
                x = int(next(iterator))
                dm.remove(x)
            elif type == "median":
                if dm.cnt_lower + dm.cnt_upper == 0:
                    results.append("Empty")
                else:
                    med = dm.get_median()
                    # Format to match potential test cases (int if whole, else float)
                    if med.is_integer():
                        results.append(str(int(med)))
                    else:
                        results.append(str(med))
        
        sys.stdout.write('\n'.join(results) + '\n')
            
    except StopIteration:
        return

if __name__ == "__main__":
    solve()
