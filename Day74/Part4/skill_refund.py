import collections

def solve():
    try:
        line = input().split()
        if not line:
            return
        
        if len(line) == 1:
            n = int(line[0])
            line2 = input().split()
            c = [int(x) for x in line2]
        else:
            c = [int(x) for x in line]
            n = len(c)
            
        if n == 0:
            print("0")
            return
        if n == 1:
            print("1")
            return
            
        # BFS
        # Can only use node i if c[i] % 2 != 0
        
        if c[0] % 2 == 0:
            print("0")
            return
            
        q = collections.deque([0])
        visited = {0}
        reached = False
        
        while q:
            u = q.popleft()
            if u == n - 1:
                reached = True
                break
                
            # Moves
            moves = [u + 1, u + c[u]]
            for v in moves:
                if 0 <= v < n:
                    if v not in visited:
                        # Can we use v?
                        if v == n - 1 or c[v] % 2 != 0:
                            visited.add(v)
                            q.append(v)
                            
        print("1" if reached else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
