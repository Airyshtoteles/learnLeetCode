import sys
from collections import deque

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            R = int(next(iterator))
            C = int(next(iterator))
        except StopIteration:
            return
            
        grid = []
        qCollapse = deque()
        distCollapse = [[float('inf')] * C for _ in range(R)]
        
        for r in range(R):
            row = []
            for c in range(C):
                val = int(next(iterator))
                row.append(val)
                if val == 1:
                    qCollapse.append((r, c))
                    distCollapse[r][c] = 0
            grid.append(row)
            
        startR = int(next(iterator))
        startC = int(next(iterator))
        targetR = int(next(iterator))
        targetC = int(next(iterator))
        
        # BFS Collapse
        dr = [0, 0, 1, -1]
        dc = [1, -1, 0, 0]
        
        while qCollapse:
            r, c = qCollapse.popleft()
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < R and 0 <= nc < C:
                    if distCollapse[nr][nc] == float('inf'):
                        distCollapse[nr][nc] = distCollapse[r][c] + 1
                        qCollapse.append((nr, nc))
                        
        # BFS Player
        if distCollapse[startR][startC] <= 0:
            print("false")
            return
            
        qPlayer = deque([(startR, startC)])
        distPlayer = [[float('inf')] * C for _ in range(R)]
        distPlayer[startR][startC] = 0
        
        found = False
        while qPlayer:
            r, c = qPlayer.popleft()
            
            if r == targetR and c == targetC:
                found = True
                break
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                if 0 <= nr < R and 0 <= nc < C:
                    if distPlayer[nr][nc] == float('inf'):
                        nextTime = distPlayer[r][c] + 1
                        if nextTime < distCollapse[nr][nc]:
                            distPlayer[nr][nc] = nextTime
                            qPlayer.append((nr, nc))
                            
        print("true" if found else "false")
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
