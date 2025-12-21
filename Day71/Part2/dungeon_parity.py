import collections

def solve():
    try:
        line = input().split()
        if not line:
            return
        a = [int(x) for x in line]
        n = len(a)
        
        if n == 0:
            print("0")
            return
        if n == 1:
            print("1")
            return
            
        visited = [False] * n
        q = collections.deque([0])
        visited[0] = True
        
        reached = False
        
        while q:
            u = q.popleft()
            if u == n - 1:
                reached = True
                break
            
            for step in [1, 2]:
                v = u + step
                if v < n and not visited[v]:
                    can_enter = False
                    if u == 0:
                        # From start, parity must match a[0]
                        if (a[0] % 2) == (a[v] % 2):
                            can_enter = True
                    else:
                        # After first step, sum is always even, so need even a[v]
                        if a[v] % 2 == 0:
                            can_enter = True
                            
                    if can_enter:
                        visited[v] = True
                        q.append(v)
                        
        print("1" if reached else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
