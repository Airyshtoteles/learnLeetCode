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

    total = 0
    attacks = 0

    for i in range(n):
        attacks += 1
        total += d[i] * attacks
        if total >= H:
            print(attacks)
            return

    # Keep using max damage
    damage = d[0]
    remaining = H - total

    while remaining > 0:
        attacks += 1
        total += damage * attacks
        remaining = H - total

    print(attacks)

if __name__ == "__main__":
    solve()
