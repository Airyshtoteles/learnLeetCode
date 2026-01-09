import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, K, N = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    # Sort descending
    D.sort(reverse=True)
    
    needed_stages = K + 1
    idx = 0
    stages_completed = 0
    
    while stages_completed < needed_stages and idx < len(D):
        current_sum = 0
        while current_sum < H and idx < len(D):
            current_sum += D[idx]
            idx += 1
            
        if current_sum >= H:
            stages_completed += 1
        else:
            break
            
    if stages_completed >= needed_stages:
        print(idx)
    else:
        print("-1")

if __name__ == "__main__":
    solve()
