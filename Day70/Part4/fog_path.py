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
        
        if grid[startR][startC] == 1 or grid[endR][endC] == 1:
            print("False")
            return
            
        visited = set()
        q = deque([(startR, startC)])
        visited.add((startR, startC))
        
        dr = [0, 0, 1, -1]
        dc = [1, -1, 0, 0]
        
        while q:
            r, c = q.popleft()
            
            if r == endR and c == endC:
                print("True")
                return
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                
                if 0 <= nr < R and 0 <= nc < C:
                    if grid[nr][nc] == 0 and (nr, nc) not in visited:
                        visited.add((nr, nc))
                        q.append((nr, nc))
                        
        print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
