import heapq

def solve():
    try:
        line = input().split()
        if not line: return
        M = int(line[0])
        N = int(line[1])
        
        grid = []
        for _ in range(M):
            grid.append(list(map(int, input().split())))
            
        cost_grid = []
        for _ in range(M):
            cost_grid.append(list(map(int, input().split())))
            
        line = input().split()
        startR, startC, targetR, targetC = map(int, line)
        
        # (cost, r, c, rot)
        pq = [(0, startR, startC, 0)]
        visited = {} # (r, c, rot) -> min_cost
        
        while pq:
            cost, r, c, rot = heapq.heappop(pq)
            
            state = (r, c, rot)
            if state in visited and visited[state] <= cost:
                continue
            visited[state] = cost
            
            # Check target
            tr, tc = targetR, targetC
            curM, curN = M, N
            for _ in range(rot):
                tr, tc = tc, curM - 1 - tr
                curM, curN = curN, curM
                
            if r == tr and c == tc:
                print(cost)
                return
            
            R = M if rot % 2 == 0 else N
            C = N if rot % 2 == 0 else M
            
            dr = [-1, 1, 0, 0]
            dc = [0, 0, -1, 1]
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                
                hit_wall = False
                if nr < 0 or nr >= R or nc < 0 or nc >= C:
                    hit_wall = True
                else:
                    # Check grid value
                    orig_r, orig_c = nr, nc
                    tempR, tempC = R, C
                    for _ in range(rot):
                        orig_r, orig_c = tempC - 1 - orig_c, orig_r
                        tempR, tempC = tempC, tempR
                    
                    if grid[orig_r][orig_c] == 1:
                        hit_wall = True
                        
                if hit_wall:
                    next_rot = (rot + 1) % 4
                    next_r, next_c = c, R - 1 - r
                    if (next_r, next_c, next_rot) not in visited or cost < visited[(next_r, next_c, next_rot)]:
                        heapq.heappush(pq, (cost, next_r, next_c, next_rot))
                else:
                    orig_r, orig_c = nr, nc
                    tempR, tempC = R, C
                    for _ in range(rot):
                        orig_r, orig_c = tempC - 1 - orig_c, orig_r
                        tempR, tempC = tempC, tempR
                        
                    new_cost = cost + cost_grid[orig_r][orig_c]
                    if (nr, nc, rot) not in visited or new_cost < visited[(nr, nc, rot)]:
                        heapq.heappush(pq, (new_cost, nr, nc, rot))
                        
        print(-1)
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
