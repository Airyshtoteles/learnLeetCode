import sys
import math

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        K = int(next(iterator))
        N = int(next(iterator))
    except StopIteration:
        return

    max_d = 0
    for _ in range(N):
        d = int(next(iterator))
        if d > max_d:
            max_d = d
            
    if H <= 0:
        print(0)
        return

    if max_d == 0:
        print("-1")
        return
        
    # L = ceil(H/D) + K
    steps = (H + max_d - 1) // max_d + K
    print(steps)

if __name__ == "__main__":
    solve()
