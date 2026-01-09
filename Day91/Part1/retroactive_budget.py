import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, N = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    if not D:
        print("NO")
        return
        
    if max(D) >= H:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
