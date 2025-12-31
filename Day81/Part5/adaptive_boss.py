import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        H = int(next(iterator))
        n = int(next(iterator))
        d = []
        for _ in range(n):
            d.append(int(next(iterator)))
    except StopIteration:
        return

    d.sort(reverse=True)

    if n == 0:
        print(-1)
        return

    if n == 1:
        # A, A, 0, A, A, 0...
        cycle_dmg = 2 * d[0]
        cycles = H // cycle_dmg
        rem = H % cycle_dmg
        attacks = cycles * 3
        
        if rem > 0:
            attacks += 1
            rem -= d[0]
        if rem > 0:
            attacks += 1
            rem -= d[0]
            
        print(attacks)
    else:
        # max1, max2...
        max1 = d[0]
        max2 = d[1]
        cycle_dmg = max1 + max2
        
        cycles = H // cycle_dmg
        rem = H % cycle_dmg
        attacks = cycles * 2
        
        if rem > 0:
            attacks += 1
            rem -= max1
        if rem > 0:
            attacks += 1
            rem -= max2
            
        print(attacks)

if __name__ == "__main__":
    solve()
