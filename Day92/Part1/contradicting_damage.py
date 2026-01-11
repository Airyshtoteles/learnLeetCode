import sys
from collections import deque

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, N = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    # BFS
    queue = deque([0])
    visited = {0}
    possible = False
    limit = 200000
    
    while queue and limit > 0:
        limit -= 1
        curr = queue.popleft()
        
        if curr >= H:
            possible = True
            break
            
        for d in D:
            nxt = curr + d
            if nxt not in visited:
                visited.add(nxt)
                queue.append(nxt)
                if nxt >= H:
                    possible = True
                    break
        if possible: break
        
    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
