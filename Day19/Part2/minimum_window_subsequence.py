# LC 727 — Minimum Window Subsequence
# Two-pointer forward then backward shrinking
from typing import List

def minWindow(s: str, t: str) -> str:
    n, m = len(s), len(t)
    if m == 0:
        return ""
    best = ""
    i = 0
    while True:
        # find first position to try
        pos = s.find(t[0], i)
        if pos == -1:
            break
        # forward scan to match t
        j = pos
        k = 0
        while j < n and k < m:
            if s[j] == t[k]:
                k += 1
            j += 1
        if k < m:
            break  # no further window possible
        end = j - 1
        # backward shrink
        k = m - 1
        j = end
        while j >= pos:
            if s[j] == t[k]:
                k -= 1
                if k < 0:
                    break
            j -= 1
        start = j + 1
        cand = s[start:end+1]
        if not best or len(cand) < len(best):
            best = cand
        i = start + 1  # next attempt moves start forward
    return best

if __name__ == "__main__":
    print(minWindow("abcdebdde", "bde"))  # bcde
