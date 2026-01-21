import sys
import math

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

    D.sort(reverse=True)
    
    current_total = 0
    moves = 0
    
    for raw_d in D:
        if current_total >= H:
            break
            
        # floor(d / sqrt(total + 1))
        # Be careful with float precision for very large numbers, 
        # but in typical CP sqrt is fine.
        
        denom = math.sqrt(current_total + 1)
        effective = math.floor(raw_d / denom)
        
        current_total += effective
        moves += 1
        
    if current_total >= H:
        print(moves)
    else:
        print("-1")

if __name__ == "__main__":
    solve()
