import sys

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        R, D, N = int(line1[0]), int(line1[1]), int(line1[2])
        
        ops = []
        for _ in range(N):
            ops.append(list(map(int, sys.stdin.readline().split())))
    except ValueError:
        return

    current_val = R
    
    # Greedy approach: Since f(x) = floor(x/a) + b is monotonic non-decreasing,
    # maximizing x at step k guarantees maximizing x at step k+1.
    
    for _ in range(D):
        next_max = -1
        for a, b in ops:
            if a == 0:
                # Should not happen based on formula, assume a>=1
                val = current_val + b
            else:
                val = (current_val // a) + b
            
            if val > next_max:
                next_max = val
        current_val = next_max
        
    print(current_val)

if __name__ == "__main__":
    solve()
