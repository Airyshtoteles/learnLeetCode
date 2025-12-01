import heapq
from typing import List

def min_time_survival(times: List[List[int]]) -> int:
    if not times:
        return -1
    n = len(times)
    if times[0][0] <= 0:
        return -1
        
    # dist[r][c]
    dist = [[float('inf')] * n for _ in range(n)]
    dist[0][0] = 0
    
    pq = [(0, 0, 0)] # time, r, c
    
    dirs = [(0,1), (0,-1), (1,0), (-1,0)]
    
    while pq:
        t, r, c = heapq.heappop(pq)
        
        if t > dist[r][c]:
            continue
        if r == n-1 and c == n-1:
            return t
            
        for dr, dc in dirs:
            nr, nc = r + dr, c + dc
            if 0 <= nr < n and 0 <= nc < n:
                nt = t + 1
                # Check if we can step on (nr, nc) at time nt
                # Must be strictly less than collapse time
                if nt < times[nr][nc]:
                    if nt < dist[nr][nc]:
                        dist[nr][nc] = nt
                        heapq.heappush(pq, (nt, nr, nc))
                        
    return -1

if __name__ == "__main__":
    times = [
        [5, 2, 1],
        [5, 4, 3],
        [1, 5, 5]
    ]
    # Path: (0,0)t=0 -> (1,0)t=1 -> (1,1)t=2 -> (1,2)t=3 -> (2,2)t=4.
    # Check constraints:
    # (0,0) 0 < 5 OK
    # (1,0) 1 < 5 OK
    # (1,1) 2 < 4 OK
    # (1,2) 3 < 3 FAIL (cannot step at t=3 if collapse at 3)
    # Wait, example logic check.
    # Try (0,0)->(0,1) [t=1 < 2 OK] -> (1,1) [t=2 < 4 OK] -> (2,1) [t=3 < 5 OK] -> (2,2) [t=4 < 5 OK].
    # Path length 4.
    print(min_time_survival(times))
