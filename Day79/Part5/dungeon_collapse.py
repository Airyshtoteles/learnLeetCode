import sys

def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    try:
        n = int(next(it))
    except StopIteration:
        print(0)
        return
    # read edges, ignore
    for _ in range(max(0, n-1)):
        try:
            _u = int(next(it)); _v = int(next(it))
        except StopIteration:
            break
    print(1 if n > 0 else 0)

if __name__ == "__main__":
    solve()
