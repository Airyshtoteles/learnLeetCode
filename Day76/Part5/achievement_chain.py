import sys
from collections import deque

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            m = int(next(iterator))
        except StopIteration:
            return
            
        adj = [[] for _ in range(n)]
        in_degree = [0] * n
        
        for _ in range(m):
            u = int(next(iterator))
            v = int(next(iterator))
            if 0 <= u < n and 0 <= v < n:
                adj[u].append(v)
                in_degree[v] += 1
                
        bonus = []
        for _ in range(n):
            bonus.append(int(next(iterator)))
            
        q = deque()
        for i in range(n):
            if in_degree[i] == 0:
                q.append(i)
                
        count = 0
        while q:
            u = q.popleft()
            count += 1
            
            # Normal dependencies
            for v in adj[u]:
                in_degree[v] -= 1
                if in_degree[v] == 0:
                    q.append(v)
            
            # Bonus
            target = bonus[u]
            if 0 <= target < n:
                in_degree[target] -= 1
                if in_degree[target] == 0:
                    q.append(target)
                    
        if count == n:
            print("true")
        else:
            print("false")
            
    except Exception:
        pass

if __name__ == "__main__":
    solve()
