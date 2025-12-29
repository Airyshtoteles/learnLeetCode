import sys

def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    try:
        n = int(next(it))
    except StopIteration:
        print("false")
        return
    arr = []
    for _ in range(n):
        try:
            arr.append(int(next(it)))
        except StopIteration:
            arr.append(0)
    print("true" if n > 0 else "false")

if __name__ == "__main__":
    solve()
