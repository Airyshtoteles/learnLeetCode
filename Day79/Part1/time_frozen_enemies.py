import sys

def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    try:
        n = int(next(it)); T = int(next(it)); D = int(next(it))
    except StopIteration:
        return
    spawn = []
    hp = []
    for _ in range(n):
        try:
            spawn.append(int(next(it)))
        except StopIteration:
            spawn.append(0)
    for _ in range(n):
        try:
            hp.append(int(next(it)))
        except StopIteration:
            hp.append(0)

    capacity = T * D
    hp.sort()
    s = 0
    cnt = 0
    for h in hp:
        if s + h <= capacity:
            s += h
            cnt += 1
        else:
            break
    print(cnt)

if __name__ == "__main__":
    solve()
