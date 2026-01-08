import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, N, K, P = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    distinct_D = sorted(list(set(D)), reverse=True)
    
    if len(distinct_D) < P:
        print("Impossible")
        return
        
    sum_val = 0
    count = 0
    
    for val in distinct_D:
        if val > 0:
            sum_val += val
            count += 1
        elif count < P:
            sum_val += val
            count += 1
            
    if sum_val > 0:
        print("Possible")
    else:
        print("Impossible")

if __name__ == "__main__":
    solve()
