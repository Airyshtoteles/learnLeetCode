import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        N = int(next(iterator))
        max_d = -float('inf')
        for _ in range(N):
            d = int(next(iterator))
            if d > max_d:
                max_d = d
    except StopIteration:
        return

    if max_d <= 0:
        print("NO")
    else:
        print("YES")

if __name__ == "__main__":
    solve()
