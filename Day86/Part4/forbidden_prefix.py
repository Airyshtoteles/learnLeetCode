import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H = int(line1[0])
        N = int(line1[1])
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    # BFS
    # Queue: (current_sum, steps)
    queue = collections.deque([(0, 0)])
    visited = {0}
    
    while queue:
        curr, steps = queue.popleft()
        
        if curr >= H:
            print(steps)
            return
            
        for d in D:
            next_val = curr + d
            if next_val not in visited:
                visited.add(next_val)
                queue.append((next_val, steps + 1))
                
    print("Impossible")

if __name__ == "__main__":
    solve()
