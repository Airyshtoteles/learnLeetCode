# Ciphered Crime Logs
# Transform by XOR with k on ASCII, then return longest palindromic substring of decoded string.
# Note: The example mapping to "level" may not match simple ASCII XOR; we implement the general method per hint.
from typing import Tuple

def xor_decode(s: str, k: int) -> str:
    return ''.join(chr(ord(c) ^ k) for c in s)

def longest_palindrome(s: str) -> str:
    if not s: return s
    n = len(s)
    start, best = 0, 1
    def expand(l: int, r: int):
        nonlocal start, best
        while l>=0 and r<n and s[l]==s[r]:
            l -= 1; r += 1
        # now s[l+1:r] is palindrome
        if r - (l+1) > best:
            best = r - (l+1)
            start = l+1
    for i in range(n):
        expand(i, i)
        expand(i, i+1)
    return s[start:start+best]

def ciphered_crime_logs(s: str, k: int) -> str:
    dec = xor_decode(s, k)
    return longest_palindrome(dec)

if __name__ == "__main__":
    print(ciphered_crime_logs("jyfwf", 7))
