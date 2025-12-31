import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        # Empty input?
        return

    s = data[0]
    if not s:
        print(0)
    else:
        print("Infinity")

if __name__ == "__main__":
    solve()
