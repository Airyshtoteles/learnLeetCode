import sys

# Increase recursion depth for deep trees
sys.setrecursionlimit(200000)

def solve():
    try:
        input = sys.stdin.read
        data = input().split()
        if not data:
            return
            
        iterator = iter(data)
        try:
            n = int(next(iterator))
        except StopIteration:
            return

        if n == 0:
            print(0)
            return

        adj = [[] for _ in range(n)]
        for _ in range(n - 1):
            u = int(next(iterator))
            w = int(next(iterator))
            adj[u].append(w)
            adj[w].append(u)
            
        v = []
        for _ in range(n):
            v.append(int(next(iterator)))
            
        dp = [0] * n
        
        # Iterative DFS to avoid recursion limit issues if tree is very deep
        # Post-order traversal needed
        parent = [-1] * n
        order = []
        stack = [0]
        
        while stack:
            u = stack.pop()
            order.append(u)
            for child in adj[u]:
                if child != parent[u]:
                    parent[child] = u
                    stack.append(child)
                    
        # Process in reverse order (leaves to root)
        for u in reversed(order):
            sum_children = 0
            for child in adj[u]:
                if child != parent[u]:
                    sum_children += dp[child]
            
            dp[u] = max(v[u], sum_children)
            
        print(dp[0])
            
    except Exception:
        pass

if __name__ == "__main__":
    solve()
