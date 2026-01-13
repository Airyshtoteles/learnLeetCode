import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        W_init = float(next(iterator))
        W_target = float(next(iterator))
        R = float(next(iterator))
        N = int(next(iterator))
        deltas = []
        for _ in range(N):
            deltas.append(float(next(iterator)))
    except StopIteration:
        return

    # Sort descending
    deltas.sort(reverse=True)
    
    current_W = W_init
    possible = True
    
    for d in deltas:
        prev_W = current_W
        grew_W = current_W * R
        next_W = grew_W + d
        
        # Check monotonicity
        if next_W < prev_W - 1e-9:
            possible = False
            break
            
        current_W = next_W
        
    if possible and current_W >= W_target - 1e-9:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
