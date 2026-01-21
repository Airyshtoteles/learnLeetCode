import sys
import math

def solve():
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    iterator = iter(input_data)
    try:
        N_seeds = int(next(iterator))
        Q_limit = int(next(iterator))
        Rows = int(next(iterator))
        Cols = int(next(iterator))
        
        maps = []
        for _ in range(N_seeds):
            curr_map = []
            for _ in range(Rows):
                curr_map.append(next(iterator))
            maps.append(tuple(curr_map))
            
    except StopIteration:
        return
        
    unique_maps = set(maps)
    U = len(unique_maps)
    
    # Can we distinguish U maps with Q bits?
    # 2^Q >= U
    if (1 << Q_limit) >= U:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
