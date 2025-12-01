# LC 76 — Minimum Window Substring
from typing import Dict

def minWindow(s: str, t: str) -> str:
    if not t or not s or len(t) > len(s):
        return ""
    need = [0]*128
    for ch in t:
        need[ord(ch)] += 1
    missing = len(t)
    left = 0
    best_len = float('inf')
    best = (0, 0)
    for right, ch in enumerate(s):
        idx = ord(ch)
        if need[idx] > 0:
            missing -= 1
        need[idx] -= 1
        while missing == 0:
            if right - left + 1 < best_len:
                best_len = right - left + 1
                best = (left, right + 1)
            # pop from left
            lch = s[left]
            need[ord(lch)] += 1
            if need[ord(lch)] > 0:
                missing += 1
            left += 1
    return s[best[0]:best[1]] if best_len != float('inf') else ""

if __name__ == "__main__":
    print(minWindow("ADOBECODEBANC", "ABC"))  # "BANC"
