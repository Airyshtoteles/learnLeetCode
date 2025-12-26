import sys

def solve():
    try:
        line1 = sys.stdin.read().split()
        if not line1:
            return
        
        iterator = iter(line1)
        n = int(next(iterator))
        H = int(next(iterator))
        
        dot = []
        for _ in range(n):
            dot.append(int(next(iterator)))
            
        dot.sort(reverse=True)
        
        min_time = float('inf')
        
        current_rate = 0
        damage_during_setup = 0
        
        for k in range(1, n + 1):
            # Add k-th DoT (index k-1)
            current_rate += dot[k-1]
            damage_during_setup += current_rate
            
            if damage_during_setup >= H:
                time_needed = k
            else:
                remaining = H - damage_during_setup
                wait_ticks = (remaining + current_rate - 1) // current_rate
                time_needed = k + wait_ticks
            
            if time_needed < min_time:
                min_time = time_needed
                
        print(min_time)
        
    except StopIteration:
        pass

if __name__ == "__main__":
    solve()
