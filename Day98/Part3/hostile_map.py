import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N = int(next(iterator))
        M = int(next(iterator))
        W = int(next(iterator))
        X = int(next(iterator))
        sr = int(next(iterator))
        sc = int(next(iterator))
        tr = int(next(iterator))
        tc = int(next(iterator))
    except StopIteration:
        return

    # If Adversary can change map, he can reset our progress.
    # Infinite loop is possible if W > 0.
    if W == 0:
        print(abs(sr - tr) + abs(sc - tc))
    else:
        print("-1")

if __name__ == "__main__":
    solve()
