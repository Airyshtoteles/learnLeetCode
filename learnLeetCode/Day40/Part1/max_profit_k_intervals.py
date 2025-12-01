from bisect import bisect_right
from typing import List, Tuple

def max_profit_k(jobs: List[Tuple[int,int,int]], K: int) -> int:
    if not jobs or K <= 0:
        return 0
    jobs = sorted(jobs, key=lambda x: x[1])  # by end
    n = len(jobs)
    ends = [e for _,e,_ in jobs]
    prev = [0]*n
    for i,(s,e,p) in enumerate(jobs):
        idx = bisect_right(ends, s) - 1
        prev[i] = idx
    dp_prev = [0]*(n+1)
    for k in range(1, K+1):
        dp_cur = [0]*(n+1)
        for i in range(1, n+1):
            s,e,p = jobs[i-1]
            pick = p + (dp_prev[prev[i-1]+1] if prev[i-1] >= 0 else 0)
            dp_cur[i] = max(dp_cur[i-1], pick)
        dp_prev = dp_cur
    return dp_prev[n]

if __name__ == "__main__":
    jobs = [(1,3,50),(2,4,10),(3,5,40),(3,6,70)]
    print(max_profit_k(jobs, 2))  # Expected 120 (50+70)
