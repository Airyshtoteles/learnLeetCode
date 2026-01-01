import sys
from collections import deque

def solve():
    input = sys.stdin.read
    data = input().split()
    if not data:
        return

    iterator = iter(data)
    try:
        R = int(next(iterator))
        C = int(next(iterator))
        k = int(next(iterator))
        grid = []
        for _ in range(R):
            grid.append(next(iterator))
    except StopIteration:
        return

    startR, startC = -1, -1
    targetR, targetC = -1, -1
    
    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'S':
                startR, startC = r, c
            elif grid[r][c] == 'T':
                targetR, targetC = r, c

    # BFS with memory state
    q = deque()
    visited = set()
    
    initial_mem = tuple()
    q.append(((startR, startC), initial_mem))
    visited.add(((startR, startC), initial_mem))
    
    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]
    
    found = False
    
    while q and not found:
        (r, c), mem = q.popleft()
        
        if r == targetR and c == targetC:
            found = True
            break
        
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            
            if 0 <= nr < R and 0 <= nc < C and grid[nr][nc] != '#':
                # Check if in memory
                in_memory = (nr, nc) in mem
                
                if not in_memory or (nr == targetR and nc == targetC):
                    new_mem = list(mem) + [(nr, nc)]
                    if len(new_mem) > k:
                        new_mem = new_mem[-k:]
                    new_mem = tuple(new_mem)
                    
                    new_state = ((nr, nc), new_mem)
                    if new_state not in visited:
                        visited.add(new_state)
                        q.append(new_state)
                        
    if found:
        print("true")
    else:
        print("false")

if __name__ == "__main__":
    solve()
