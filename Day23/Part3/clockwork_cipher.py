# The Clockwork Cipher
# We have values mod 12; an operation increments +1 on a circular segment [a..b] (inclusive, wrap allowed).
# Goal: minimal number of operations to make all values equal.
# Approach: try all target t in 0..11. For each t, compute inc[i] = (t - A[i]) mod 12.
# For circular range increments, minimal ops equals minimal sum of positive jumps of inc along some rotation break.
# So we try all rotations and compute ops = sum(max(0, inc_rot[i] - inc_rot[i-1])) with inc_rot[-1]=0.
from typing import List

def min_ops_to_uniform(gears: List[int]) -> int:
    if not gears: return 0
    n = len(gears)
    ans = 10**9
    for t in range(12):
        inc = [(t - x) % 12 for x in gears]
        # test all rotations: break between r-1 and r
        for r in range(n):
            # build rotated inc starting at r
            rot = inc[r:]+inc[:r]
            ops = 0
            prev = 0
            for x in rot:
                if x > prev:
                    ops += x - prev
                prev = x
            ans = min(ans, ops)
    return ans

if __name__ == "__main__":
    print(min_ops_to_uniform([3,5,7,1]))  # sample expectation 8
