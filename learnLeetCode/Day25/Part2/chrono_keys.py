# The Chrono Keys
# Functional graph by portals; time accumulates by timeShift at each visit (including final floor).
# Determine if we can reach floor n-1 with exact time = target.
# Strategy: walk from 0 following portals, detect cycle. If n-1 unreachable -> False.
# If we hit n-1 on the path (before cycle), check time. If n-1 is within a cycle, collect the first time b we reach it and cycle sum C; check if target ≡ b (mod C) with k ≥ 0.
from typing import List

def can_reach_target(timeShift: List[int], portal: List[int], target: int) -> bool:
    n = len(timeShift)
    nxt = portal[:]
    cur = 0
    seen_idx = [-1]*n
    seen_time = [0]*n
    t = 0
    step = 0
    # simulate until cycle or termination
    while cur != -1 and seen_idx[cur] == -1:
        seen_idx[cur] = step
        # apply shift at current
        t += timeShift[cur]
        seen_time[cur] = t
        if cur == n-1 and t == target:
            return True
        cur = nxt[cur]
        step += 1
    if cur == -1:
        return False
    # cycle detected starting at cur
    start_idx = seen_idx[cur]
    start_time = seen_time[cur]
    # compute cycle order and sum
    cycle_nodes = []
    u = cur
    C = 0
    while True:
        cycle_nodes.append(u)
        C += timeShift[u]
        u = nxt[u]
        if u == cur or u == -1:
            break
    # If cycle breaks to -1 (shouldn't in functional graph unless -1 inside), treat as termination
    if u == -1:
        # path escapes? Not possible from inside cycle; but we handle conservatively as no infinite accumulation
        # Try checking along the tail only already handled; thus return False
        return False
    # Check if n-1 is in the cycle and compute first time b when we are at n-1 within the cycle
    if (n-1) in cycle_nodes:
        # reconstruct first cycle traversal times starting from cur at time=start_time
        b = None
        tt = start_time
        v = cur
        # move one full cycle
        while True:
            if v == n-1:
                b = tt
                break
            v = nxt[v]
            tt += timeShift[v]
            if v == cur:
                break
        if b is None:
            return False
        if C == 0:
            return b == target
        # check solvability: target = b + k*C, k >= 0 integer
        diff = target - b
        # divisibility check with sign
        if diff % C == 0 and diff // C >= 0:
            return True
        return False
    else:
        # n-1 not in cycle; if it was seen before cycle, we already checked equality on first hit only
        return False

if __name__ == "__main__":
    timeShift = [3,-2,4,1]
    portal = [1,2,3,-1]
    print(can_reach_target(timeShift, portal, 6))  # True
