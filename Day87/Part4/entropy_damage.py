import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, N = int(line1[0]), int(line1[1])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        E = float(line2[0])
        
        line3 = sys.stdin.readline().split()
        if not line3: D = []
        else: D = [int(x) for x in line3]
    except ValueError:
        return

    max_d = -float('inf')
    for d in D:
        if d > max_d: max_d = d
        
    if max_d > 0:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
