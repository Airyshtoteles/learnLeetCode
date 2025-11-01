from collections import deque
from typing import List

def min_presses(n: int, m: int, connections: List[List[int]]) -> int:
    masks = [0]*n
    for i, lamps in enumerate(connections):
        mask = 0
        for lamp in lamps:
            mask ^= (1 << lamp)
        masks[i] = mask
    target = (1 << m) - 1
    q = deque([0])
    dist = {0: 0}
    while q:
        s = q.popleft()
        if s == target:
            return dist[s]
        d = dist[s]
        for i in range(n):
            ns = s ^ masks[i]
            if ns not in dist:
                dist[ns] = d + 1
                q.append(ns)
    return -1

if __name__ == "__main__":
    n = 3; m = 3
    connections = [
        [0,1],
        [1,2],
        [0,2],
    ]
    print(min_presses(n, m, connections))  # Expected 3
