from collections import deque

def solve():
    try:
        line = input().split()
        if not line: return
        R = int(line[0])
        C = int(line[1])
        
        grid = []
        for _ in range(R):
            grid.append(list(map(int, input().split())))
            
        line = input().split()
        startR, startC, endR, endC = map(int, line)
        
        # visited[r][c][cooldown]
        visited = set()
        q = deque([(startR, startC, 0)])
        visited.add((startR, startC, 0))
        
        dr = [0, 0, 1, -1]
        dc = [1, -1, 0, 0]
        
        while q:
            r, c, cooldown = q.popleft()
            
            if r == endR and c == endC:
                print("True")
                return
            
            next_cooldown_base = 0
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                
                if 0 <= nr < R and 0 <= nc < C:
                    new_cooldown = next_cooldown_base
                    possible = True
                    
                    if grid[nr][nc] == 1:
                        if cooldown > 0:
                            possible = False
                        else:
                            new_cooldown = 1
                            
                    if possible and (nr, nc, new_cooldown) not in visited:
                        visited.add((nr, nc, new_cooldown))
                        q.append((nr, nc, new_cooldown))
                        
        print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
