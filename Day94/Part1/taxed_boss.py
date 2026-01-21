import sys

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    iterator = iter(input_data)
    try:
        H = int(next(iterator))
        K = int(next(iterator))
        N = int(next(iterator))
        damages = []
        for _ in range(N):
            damages.append(int(next(iterator)))
    except StopIteration:
        return

    if H <= 0:
        print(0)
        return

    max_d = max(damages) if damages else 0
    
    if max_d == 0:
        print("-1")
        return

    current_total = 0
    steps = 0
    
    while current_total < H:
        tax = current_total // K
        eff = max_d - tax
        if eff <= 0:
            print("-1")
            return
        
        current_total += eff
        steps += 1
        
    print(steps)

if __name__ == "__main__":
    solve()
