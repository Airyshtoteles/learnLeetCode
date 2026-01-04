import sys
import math

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, K = int(line1[0]), int(line1[1])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        N_types = int(line2[0])
        
        line3 = sys.stdin.readline().split()
        if not line3: return
        D = [int(x) for x in line3]
    except ValueError:
        return

    if not D:
        print(-1)
        return

    max_dmg = max(D)
    if max_dmg == 0:
        print(-1)
        return

    # (N - 1) * max_dmg >= H
    # N >= ceil(H / max_dmg) + 1
    
    if K == 0:
        ans = (H + max_dmg - 1) // max_dmg
    else:
        ans = (H + max_dmg - 1) // max_dmg + 1
        
    print(ans)

if __name__ == "__main__":
    solve()
