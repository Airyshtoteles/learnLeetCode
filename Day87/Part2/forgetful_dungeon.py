import sys
import heapq

def solve():
    try:
        line1 = sys.stdin.readline().split()
        if not line1: return
        N, M, K = map(int, line1)
        
        line2 = sys.stdin.readline().split()
        if not line2: return
        rows = [int(line2[0]), int(line2[1]), int(line2[2]), int(line2[3])] # StartR StartC TargetR TargetC
        StartR, StartC, TargetR, TargetC = rows
        
        grid = []
        for _ in range(N):
            grid.append(sys.stdin.readline().strip())
    except ValueError:
        return

    # Dijkstra
    dist = [[float('inf')] * M for _ in range(N)]
    dist[StartR][StartC] = 0
    pq = [(0, StartR, StartC)]
    
    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]
    
    while pq:
        d, r, c = heapq.heappop(pq)
        
        if d > dist[r][c]: continue
        if r == TargetR and c == TargetC:
            if d <= K:
                print("Possible")
            else:
                print("Impossible")
            return
            
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            
            if 0 <= nr < N and 0 <= nc < M:
                cost = 2 if grid[nr][nc] == '#' else 1
                if dist[nr][nc] > d + cost:
                    dist[nr][nc] = d + cost
                    heapq.heappush(pq, (dist[nr][nc], nr, nc))
                    
    print("Impossible")

if __name__ == "__main__":
    solve()
