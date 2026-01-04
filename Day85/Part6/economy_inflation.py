import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        G, C, L, W = int(line1[0]), int(line1[1]), int(line1[2]), int(line1[3])
    except ValueError:
        return

    if C == 0:
        if G > 0:
            print("Possible")
        elif W <= 0:
            print("Possible")
        else:
            print("Impossible")
        return

    if L <= 1:
        print("Impossible")
        return

    # Max k such that 1 + k * C < L
    # k * C < L - 1
    # k <= (L - 1 - 1) // C
    k_max = (L - 2) // C
    
    if k_max < 0:
        print("Impossible")
        return

    # Check Value(k_max) >= W
    # (k * G) / (1 + k * C) >= W
    # k * G >= W * (1 + k * C)
    
    lhs = k_max * G
    rhs = W * (1 + k_max * C)
    
    if lhs >= rhs:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
