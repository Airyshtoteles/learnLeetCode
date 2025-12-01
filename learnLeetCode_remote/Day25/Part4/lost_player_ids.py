# The Lost Player IDs
# Trick: missing ID = XOR(1..n) XOR XOR(players appearing odd number of times in swap records).
from typing import List, Tuple

def missing_id(n: int, records: List[Tuple[int,int]]) -> int:
    xr = 0
    for i in range(1, n+1):
        xr ^= i
    freq = [0]*(n+1)
    for a,b in records:
        if 1<=a<=n: freq[a] ^= 1
        if 1<=b<=n: freq[b] ^= 1
    for i in range(1, n+1):
        if freq[i]:
            xr ^= i
    return xr

if __name__ == "__main__":
    n=5; records=[[1,2],[3,4],[2,3]]
    print(missing_id(n, records))  # 5
