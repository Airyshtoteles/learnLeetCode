import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H = int(line1[0])
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        N = int(line2[0])
        
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

    # Logic: Max stackable damage is 2 * max_dmg.
    # Step 1: D.
    # Step 2: 2D. (Then reduces to D).
    # Step 3: 2D.
    
    if H <= max_dmg:
        print(1)
    elif H <= 2 * max_dmg:
        print(2)
    else:
        print(-1)

if __name__ == "__main__":
    solve()
