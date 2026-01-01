import sys

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    n = int(data[0])
    c = []
    for i in range(n):
        c.append(int(data[1 + i]))

    total_rewind = sum(c)

    if total_rewind == 0:
        print("true")
    elif total_rewind > 0:
        print("false")
    else:
        print("true")

if __name__ == "__main__":
    solve()
