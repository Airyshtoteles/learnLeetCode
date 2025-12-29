import sys

def solve():
    data = sys.stdin.read().strip().split()
    if not data:
        return
    it = iter(data)
    try:
        n = int(next(it))
    except StopIteration:
        return
    # read cooldowns but unused for single-use
    c = []
    for _ in range(n):
        try:
            c.append(int(next(it)))
        except StopIteration:
            c.append(0)
    print(n)

if __name__ == "__main__":
    solve()
