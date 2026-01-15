import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        N = int(next(iterator))
        max_d = -float('inf')
        for _ in range(N):
            val = int(next(iterator))
            if val > max_d:
                max_d = val
                
        if H <= 0:
            print("YES")
        elif max_d > 0:
            print("YES")
        else:
            print("NO")
            
    except StopIteration:
        return

if __name__ == "__main__":
    solve()
