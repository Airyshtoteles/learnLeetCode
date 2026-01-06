import sys
import collections

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, Dim = int(line1[0]), int(line1[1])
        
        skills = []
        for _ in range(N):
            skills.append(tuple(map(int, sys.stdin.readline().split())))
            
        Target = tuple(map(int, sys.stdin.readline().split()))
    except ValueError:
        return

    # BFS
    start = tuple([0]*Dim)
    queue = collections.deque([start])
    visited = {start}
    
    while queue:
        curr = queue.popleft()
        
        if curr == Target:
            print("Possible")
            return
            
        for skill in skills:
            next_val = tuple(a + b for a, b in zip(curr, skill))
            
            if next_val not in visited:
                visited.add(next_val)
                queue.append(next_val)
                
    print("Impossible")

if __name__ == "__main__":
    solve()
