import sys

def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    try:
        H = int(next(it)); k = int(next(it))
    except StopIteration:
        return
    if H <= 0:
        print(0)
        return
    if H == 1:
        print(0)
        return
    print((H - 1) * k)

if __name__ == "__main__":
    solve()
