import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        n = int(next(iterator))
        k = int(next(iterator))
        t = []
        for _ in range(n):
            t.append(int(next(iterator)))
    except StopIteration:
        return

    t.sort()

    if n == 0:
        print(0)
        return

    count = 1
    last_t = t[0]

    for i in range(1, n):
        if t[i] - last_t <= k:
            last_t = t[i]
        else:
            count += 1
            last_t = t[i]

    print(count)

if __name__ == "__main__":
    solve()
