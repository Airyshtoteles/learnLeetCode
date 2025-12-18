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
        startR, startC, targetR, targetC = map(int, line)
        
        # visited[r][c][step_mod_4]
        visited = set()
        q = deque([(startR, startC, 0)])
        visited.add((startR, startC, 0))
        
        dr = [0, 0, 1, -1]
        dc = [1, -1, 0, 0]
        
        while q:
            r, c, steps = q.popleft()
            
            # Check target
            tr, tc = targetR, targetC
            if (steps // 2) % 2 == 1:
                tr, tc = R - 1 - targetR, C - 1 - targetC
                
            if r == tr and c == tc:
                print("True")
                return
            
            next_steps = steps + 1
            next_mod = next_steps % 4
            
            for i in range(4):
                nr, nc = r + dr[i], c + dc[i]
                
                if 0 <= nr < R and 0 <= nc < C:
                    # Check wall
                    check_r, check_c = nr, nc
                    if (steps // 2) % 2 == 1:
                        check_r, check_c = R - 1 - nr, C - 1 - nc
                        
                    if grid[check_r][check_c] == 0:
                        final_r, final_c = nr, nc
                        if next_steps % 2 == 0:
                            final_r, final_c = R - 1 - nr, C - 1 - nc
                            
                        if (final_r, final_c, next_mod) not in visited:
                            visited.add((final_r, final_c, next_mod))
                            q.append((final_r, final_c, next_steps))
                            
        print("False")
    except EOFError:
        pass

if __name__ == "__main__":
    solve()
