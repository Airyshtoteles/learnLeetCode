import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N = int(line1[0])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        D = [int(x) for x in line2]
    except ValueError:
        return

    # Filter positive
    pos_D = [x for x in D if x > 0]
    pos_D.sort()
    
    total = 0
    for i, val in enumerate(pos_D):
        total += (i + 1) * val
        
    print(total)

if __name__ == "__main__":
    solve()
