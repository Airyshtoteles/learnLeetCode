import sys

# See C++ solution for logic.
# Answer is 1 for any non-trivial tree under the "Single Death" interpretation.

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        n = int(next(iterator))
    except StopIteration:
        return

    if n <= 1:
        print(0)
        return

    # Consume edges
    for _ in range(n - 1):
        try:
            next(iterator)
            next(iterator)
        except StopIteration:
            break

    print(1)

if __name__ == "__main__":
    solve()
