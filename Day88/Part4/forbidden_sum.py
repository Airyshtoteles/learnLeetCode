import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H = int(line1[0])
        N_D = int(line1[1])
        N_F = int(line1[2])
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
        
        line3 = sys.stdin.readline().split()
        if not line3: F = set()
        else: F = set(int(x) for x in line3)
    except ValueError:
        return

    max_F = 0
    if F:
        max_F = max(F)
        
    has_pos = any(d > 0 for d in D)
    limit = max_F + 2000
    
    queue = collections.deque([0])
    visited = {0}
    
    while queue:
        curr = queue.popleft()
        
        if curr >= H:
            print("Possible")
            return
            
        if curr > max_F and has_pos:
            print("Possible")
            return
            
        for d in D:
            next_val = curr + d
            if next_val < 0: continue
            
            if next_val in F: continue
            if next_val in visited: continue
            
            if next_val <= limit or next_val >= H:
                visited.add(next_val)
                queue.append(next_val)
                
    print("Impossible")

if __name__ == "__main__":
    solve()
