import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, N = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    D.sort()
    
    current_sum = 0
    steps = 0
    current_avg = -1.0
    possible = False
    
    while True:
        target = current_avg
        if steps == 0: target = -1.0
        
        best_d = -1
        found = False
        
        for val in D:
            if float(val) > target:
                best_d = val
                found = True
                break
                
        if not found:
            break
            
        current_sum += best_d
        steps += 1
        current_avg = current_sum / steps
        
        if current_sum >= H:
            possible = True
            break
            
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
