import sys
import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def solve():
    try:
        input_data = sys.stdin.read().split()
    except Exception:
        return
        
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        N = int(next(iterator))
    except StopIteration:
        return

    current_gcd = 0
    first = True
    
    for _ in range(N):
        d = int(next(iterator))
        if first:
            current_gcd = d
            first = False
        else:
            current_gcd = gcd(current_gcd, d)
            
    if not first and current_gcd == 1:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
