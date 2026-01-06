import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, N = int(line1[0]), int(line1[1])
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    if not D:
        print("Impossible")
        return

    total_dmg = sum(D)
    max_dmg = max(D)

    # Robustness check: Total - Max >= H
    if total_dmg - max_dmg >= H:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
