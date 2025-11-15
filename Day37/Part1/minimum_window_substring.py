from collections import Counter

def min_window(s: str, t: str) -> str:
    if not t or not s:
        return ""
    need = Counter(t)
    required = len(need)
    formed = 0
    window = {}
    l = 0
    ans = (float('inf'), None, None)
    for r, ch in enumerate(s):
        window[ch] = window.get(ch, 0) + 1
        if ch in need and window[ch] == need[ch]:
            formed += 1
        while l <= r and formed == required:
            if r - l + 1 < ans[0]:
                ans = (r - l + 1, l, r)
            lc = s[l]
            window[lc] -= 1
            if lc in need and window[lc] < need[lc]:
                formed -= 1
            l += 1
    return "" if ans[0] == float('inf') else s[ans[1]:ans[2]+1]

if __name__ == "__main__":
    print(min_window("ADOBECODEBANC", "ABC"))  # Expected "BANC"
