def can_achieve(target, k, mana):
    needed = 0
    available = 0
    for m in mana:
        if m < target:
            needed += (target - m)
        else:
            available += (m - target)
    
    # We need enough available mana to cover the need.
    # And the total amount moved (needed) must not exceed k.
    return needed <= available and needed <= k

def solve():
    import sys
    input = sys.stdin.read
    data = input().split()
    
    if not data:
        return

    n = int(data[0])
    k = int(data[1])
    mana = []
    for i in range(n):
        mana.append(int(data[2 + i]))

    low = 0
    # The maximum possible minimum is bounded by the average or just max + k roughly
    # A safe upper bound is max(mana) because we can't create mana, only move it.
    # Actually, if we just redistribute, the max possible min is sum / n.
    # But let's stick to a loose upper bound for binary search safety.
    high = max(mana) + k + 1 
    ans = 0

    while low <= high:
        mid = (low + high) // 2
        if can_achieve(mid, k, mana):
            ans = mid
            low = mid + 1
        else:
            high = mid - 1
            
    print(ans)

if __name__ == "__main__":
    solve()
