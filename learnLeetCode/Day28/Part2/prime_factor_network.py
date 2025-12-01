from typing import List

class DSU:
    def __init__(self, n: int):
        self.p = list(range(n))
        self.r = [0]*n
    def find(self, x):
        while self.p[x] != x:
            self.p[x] = self.p[self.p[x]]
            x = self.p[x]
        return x
    def union(self, a, b):
        ra, rb = self.find(a), self.find(b)
        if ra == rb: return False
        if self.r[ra] < self.r[rb]: ra, rb = rb, ra
        self.p[rb] = ra
        if self.r[ra] == self.r[rb]: self.r[ra] += 1
        return True

def factor(n: int) -> List[int]:
    res = []
    d = 2
    x = n
    while d*d <= x:
        if x % d == 0:
            res.append(d)
            while x % d == 0:
                x //= d
        d += 1 if d == 2 else 2  # after 2, test only odd numbers
    if x > 1:
        res.append(x)
    return res

def count_components(nums: List[int]) -> int:
    n = len(nums)
    dsu = DSU(n)
    prime_owner = {}
    for i, v in enumerate(nums):
        primes = factor(v)
        for p in primes:
            if p in prime_owner:
                dsu.union(i, prime_owner[p])
            else:
                prime_owner[p] = i
    roots = set(dsu.find(i) for i in range(n))
    return len(roots)

if __name__ == "__main__":
    nums = [2,3,6,15,35]
    print(count_components(nums))  # Expected 2
