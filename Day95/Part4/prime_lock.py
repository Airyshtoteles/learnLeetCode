import sys
import math

def gcd(a, b):
    while b:
        a, b = b, a % b
    return a

def is_prime(n):
    if n <= 1: return False
    for i in range(2, int(math.isqrt(n)) + 1):
        if n % i == 0: return False
    return True

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        N = int(next(iterator))
        D = []
        for _ in range(N):
            D.append(int(next(iterator)))
    except StopIteration:
        return

    if not D:
        print("NO")
        return

    g = D[0]
    for x in D[1:]:
        g = gcd(g, x)

    if g == 1:
        print("YES")
    else:
        # Reaching only multiples of g
        if g >= H and is_prime(g):
            print("YES")
        else:
            print("NO")

if __name__ == "__main__":
    solve()
