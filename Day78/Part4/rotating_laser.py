import sys

def solve():
    try:
        input_data = sys.stdin.read().split()
        if not input_data:
            return
        
        iterator = iter(input_data)
        try:
            n = int(next(iterator))
            m = int(next(iterator))
            startR = int(next(iterator))
            startC = int(next(iterator))
            dir = int(next(iterator))
            k = int(next(iterator))
        except StopIteration:
            return
            
        # 0=N, 1=E, 2=S, 3=W
        dr = [-1, 0, 1, 0]
        dc = [0, 1, 0, -1]
        
        r, c = startR, startC
        visited_cells = set()
        
        if 0 <= r < n and 0 <= c < m:
            visited_cells.add((r, c))
        else:
            print(0)
            return
            
        visited_states = set()
        step_mod = 0
        
        while True:
            state = (r, c, dir, step_mod)
            if state in visited_states:
                break
            visited_states.add(state)
            
            r += dr[dir]
            c += dc[dir]
            step_mod = (step_mod + 1) % k
            
            if not (0 <= r < n and 0 <= c < m):
                break
                
            visited_cells.add((r, c))
            
            if step_mod == 0:
                dir = (dir + 1) % 4
                
        print(len(visited_cells))
        
    except Exception:
        pass

if __name__ == "__main__":
    solve()
