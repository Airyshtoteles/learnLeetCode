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

    # We need (N - K) * max_dmg >= H
    # Let X = N - K (effective attacks)
    # X * max_dmg >= H
    # X >= ceil(H / max_dmg)
    
    X = (H + max_dmg - 1) // max_dmg
    N = K + X
    
    print(N)

if __name__ == "__main__":
    solve()
