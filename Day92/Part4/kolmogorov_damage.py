import sys
import math

def solve():
    try:
        line = sys.stdin.readline().split()
        if not line: return
        H = int(line[0])
        K = int(line[1])
    except ValueError:
        return

    if H == 0:
        print("YES")
        return

    # Max length of simple string L < 2^K
    # Max value ~ 2^L
    
    if K >= 10: # 2^10 = 1024 length. 2^1024 huge.
        print("YES")
        return
        
    max_L = 1 << K # 2^K
    
    # Value is 2^max_L - 1
    # Python handles large ints automatically
    capacity = (1 << max_L) - 1
    
    if capacity >= H:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
