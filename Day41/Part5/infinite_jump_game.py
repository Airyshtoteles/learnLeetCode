from collections import deque
from typing import List

def can_reach_end(A: List[int], c: int) -> bool:
    n = len(A)
    if n == 0:
        return False
    if n == 1:
        return True  # already at target
    original = A[:]  # keep originals
    visits = [0]*n   # number of times we've incremented (landed minus first)
    # queue of positions to process; each processing uses current A[pos]
    q = deque([0])
    seen_state = [set() for _ in range(n)]  # store jump length processed from pos
    while q:
        pos = q.popleft()
        cur_jump = A[pos]
        if cur_jump in seen_state[pos]:
            # already processed this jump size from pos
            continue
        seen_state[pos].add(cur_jump)
        # attempt jumps
        for nxt in (pos + cur_jump, pos - cur_jump):
            if 0 <= nxt < n:
                if nxt == n-1:
                    return True
                q.append(nxt)
        # After processing outgoing jumps, simulate landing effect for pos (already landed earlier). Increase if allowed.
        if visits[pos] < c:
            visits[pos] += 1
            A[pos] += 1
            if visits[pos] == c:
                A[pos] = 0  # lock
            # new jump length might create new transitions later; re-enqueue
            q.append(pos)
    return False

if __name__ == "__main__":
    print(can_reach_end([2,3,1,1,4], 2))
