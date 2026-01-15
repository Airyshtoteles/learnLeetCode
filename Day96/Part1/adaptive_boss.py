import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        N = int(next(iterator))
        D = []
        max_d = 0
        for _ in range(N):
            val = int(next(iterator))
            if val > max_d:
                max_d = val
            D.append(val)
            
        if max_d >= H:
            print(1)
        else:
            print("-1")
            
    except StopIteration:
        return

if __name__ == "__main__":
    solve()
