import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
    except Exception:
        return

    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        W_init = int(next(iterator))
        W_target = int(next(iterator))
        T_delay = int(next(iterator))
        N = int(next(iterator))
    except StopIteration:
        return

    can_grow = False
    
    for _ in range(N):
        cost = int(next(iterator))
        gain = int(next(iterator))
        
        if gain > cost:
            if W_init >= cost:
                can_grow = True
                
    if W_init >= W_target:
        print("YES")
    elif can_grow:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
