import sys

# Increase recursion depth for deep DFS
sys.setrecursionlimit(2000)

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        H, M, N = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: D = []
        else: D = [int(x) for x in line2]
    except ValueError:
        return

    if H == 0:
        print("YES")
        return

    D.sort(reverse=True)
    max_d = D[0] if D else 0
    visited = [False] * M
    visited[0] = True
    
    # Use a stack-based DFS to avoid recursion limit issues and overhead
    # Stack stores: (u, current_sum, depth, edge_index)
    # But for backtracking we need to unset visited.
    # Recursive is cleaner, let's use it with setrecursionlimit.
    
    possible = False

    def dfs(u, current_sum, depth):
        nonlocal possible
        if possible: return
        
        if current_sum >= H:
            possible = True
            return

        remaining_steps = M - 1 - depth
        if remaining_steps <= 0: return
        
        # Pruning
        if current_sum + remaining_steps * max_d < H:
            return

        for val in D:
            v = (u + val) % M
            if not visited[v]:
                visited[v] = True
                dfs(v, current_sum + val, depth + 1)
                visited[v] = False
                if possible: return

    dfs(0, 0, 0)

    if possible:
        print("YES")
    else:
        print("NO")

if __name__ == "__main__":
    solve()
