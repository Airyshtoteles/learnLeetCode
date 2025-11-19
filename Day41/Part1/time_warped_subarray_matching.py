from typing import List

def factor_info(x: int):
    if x == 0:
        return (0, -1)  # odd part sentinel -1, exponent unused
    e = 0
    while x % 2 == 0:
        x //= 2
        e += 1
    return (x, e)

def build_odd_array(arr: List[int]):
    odd = []
    exp = []
    for v in arr:
        o, e = factor_info(v)
        odd.append(o)
        exp.append(e)
    return odd, exp

def z_algorithm(seq: List[int]) -> List[int]:
    n = len(seq)
    z = [0]*n
    l = r = 0
    for i in range(1, n):
        if i <= r:
            z[i] = min(r - i + 1, z[i - l])
        while i + z[i] < n and seq[z[i]] == seq[i + z[i]]:
            z[i] += 1
        if i + z[i] - 1 > r:
            l, r = i, i + z[i] - 1
    z[0] = n
    return z

def can_time_warp_subarray(A: List[int], B: List[int], k: int) -> bool:
    n, m = len(A), len(B)
    if m > n:
        return False
    oddA, expA = build_odd_array(A)
    oddB, expB = build_odd_array(B)
    # Quick zero feasibility check
    for i in range(m):
        if oddB[i] == -1:  # B[i]==0
            # require A subarray element also zero
            pass
    # Pattern matching on odd parts
    sentinel = 10**11 + 7
    combined = oddB + [sentinel] + oddA
    z = z_algorithm(combined)
    for start in range(n - m + 1):
        # position in combined is m+1+start
        if z[m + 1 + start] >= m:
            # verify exponent cost and zero compatibility
            total = 0
            ok = True
            for t in range(m):
                if oddB[t] == -1:
                    if oddA[start + t] != -1:
                        ok = False
                        break
                    # both zero -> cost 0
                    continue
                if oddA[start + t] == -1:
                    ok = False
                    break
                total += abs(expA[start + t] - expB[t])
                if total > k:
                    ok = False
                    break
            if ok and total <= k:
                return True
    return False

if __name__ == "__main__":
    A = [4,3,8,2,16]
    B = [1,8]
    print(can_time_warp_subarray(A,B,3))  # True
