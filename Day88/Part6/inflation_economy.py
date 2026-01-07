import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        InitialMoney, TargetW, N_Trans = map(int, line1)
        
        options = []
        for _ in range(N_Trans):
            options.append(list(map(int, sys.stdin.readline().split())))
    except ValueError:
        return

    # BFS
    # Visited tracks realized Inflation values.
    # Because "Same Inflation => Collapse".
    
    queue = collections.deque([(InitialMoney, 0)]) # Money, Inflation
    seen_inflation = {0}
    
    while queue:
        curr_M, curr_I = queue.popleft()
        
        if curr_M >= TargetW:
            print("Possible")
            return
            
        for dM, dI in options:
            next_M = curr_M + dM
            next_I = curr_I + dI
            
            if next_M < 0: continue
            
            if next_I in seen_inflation:
                continue
                
            seen_inflation.add(next_I)
            queue.append((next_M, next_I))
            
    print("Impossible")

if __name__ == "__main__":
    solve()
