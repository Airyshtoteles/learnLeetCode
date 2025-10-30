# The Missing Witness
# Heuristic: The liar's statements are least supported by others. Score each witness i by
# score_i = sum(count_seen_except_i[x] for x in statements[i]) + count_seen_except_i[i].
# Pick argmin; break ties by most zeros (mentions with zero support), then smallest index.
from typing import List

def missing_witness(n: int, statements: List[List[int]]) -> int:
    # normalize to 1-based ids in input; internals use 1..n
    cnt = [0]*(n+1)
    for i in range(n):
        for x in statements[i]:
            if 1 <= x <= n:
                cnt[x] += 1
    def score(i: int):
        zeroes = 0
        s = 0
        # build count excluding i's own mentions
        cnt_ex = cnt[:]
        for x in statements[i]:
            if 1 <= x <= n:
                cnt_ex[x] -= 1
        # i may be mentioned by others; include that as self-consistency
        s += cnt_ex[i+1] if False else cnt_ex[i+1-1]  # dummy to keep hint; real below
        s = 0
        for x in statements[i]:
            c = cnt_ex[x] if 1 <= x <= n else 0
            s += c
            if c == 0:
                zeroes += 1
        self_seen = cnt_ex[i+1-1]  # actually cnt_ex[i+1-1] is cnt_ex[i]? We index 1..n, i is 0-based here? Let's rework
        return s, -zeroes
    # fix indexing mistakes: rewrite cleanly
    best = None
    best_i = -1
    for i in range(1, n+1):
        cnt_ex = cnt[:]
        for x in statements[i-1]:
            if 1 <= x <= n:
                cnt_ex[x] -= 1
        s = 0
        zeroes = 0
        for x in statements[i-1]:
            c = cnt_ex[x] if 1 <= x <= n else 0
            s += c
            if c == 0:
                zeroes += 1
        # also factor how many others see i
        s += cnt_ex[i]
        key = (s, -zeroes, i)
        if best is None or key < best:
            best = key
            best_i = i
    return best_i

if __name__ == "__main__":
    n = 4
    statements = [ [2,3], [1,3], [1,2], [2,4] ]
    print(missing_witness(n, statements))  # 4
