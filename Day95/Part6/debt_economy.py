import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        W_init = float(next(iterator))
        W_target = float(next(iterator))
        DebtLimit = float(next(iterator))
        Rate = float(next(iterator))
        N = int(next(iterator))
        
        deals = []
        for _ in range(N):
            c = float(next(iterator))
            g = float(next(iterator))
            if g > c:
                deals.append((c, g))
    except StopIteration:
        return

    # Sort by Cost Ascending
    deals.sort(key=lambda x: x[0])
    
    current_W = W_init
    reached = (current_W >= W_target)
    
    for cost, gain in deals:
        if reached: break
        
        # Check affordability: M - Cost >= -D
        if current_W - cost >= -DebtLimit - 1e-9:
            current_W = current_W - cost + gain
            
            if current_W >= W_target:
                reached = True
                break
                
            if current_W < 0:
                current_W *= (1.0 + Rate)
                
            if current_W < -DebtLimit - 1e-9:
                break
                
    if reached or current_W >= W_target:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
