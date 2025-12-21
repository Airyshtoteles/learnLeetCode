import collections

def solve():
    try:
        line1 = input().split()
        if not line1:
            return
        R, C = int(line1[0]), int(line1[1])
        
        line2 = input().split()
        sr, sc = int(line2[0]), int(line2[1])
        
        line3 = input().split()
        br, bc = int(line3[0]), int(line3[1])
        
        line4 = input().split()
        k = int(line4[0])
        
        q = collections.deque([(sr, sc, 0)])
        visited = set([(sr, sc)])
        
        possible = False
        
        dr = [-1, 1, 0, 0]
        dc = [0, 0, -1, 1]
        
        while q:
            r, c, t = q.popleft()
            
            # Check current validity (though we check before push, start needs check)
            layer = t // k
            min_r, max_r = layer, R - 1 - layer
            min_c, max_c = layer, C - 1 - layer
            
            if r < min_r or r > max_r or c < min_c or c > max_c:
                continue
                
            if r == br and c == bc:
                possible = True
                break
            
            nt = t + 1
            n_layer = nt // k
            n_min_r, n_max_r = n_layer, R - 1 - n_layer
            n_min_c, n_max_c = n_layer, C - 1 - n_layer
            
            if n_min_r > n_max_r or n_min_c > n_max_c:
                continue
                
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                
                if n_min_r <= nr <= n_max_r and n_min_c <= nc <= n_max_c:
                    if (nr, nc) not in visited:
                        visited.add((nr, nc))
                        q.append((nr, nc, nt))
                        
        print("1" if possible else "0")
            
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
