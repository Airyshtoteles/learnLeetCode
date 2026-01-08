import sys
from collections import deque

def solve():
    try:
        line = sys.stdin.readline().split()
        if not line: return
        R, C = map(int, line)
        grid = [list(sys.stdin.readline().strip()) for _ in range(R)]
    except ValueError:
        return

    alice_start = None
    bob_start = None

    for r in range(R):
        for c in range(C):
            if grid[r][c] == 'A':
                alice_start = (r, c)
                grid[r][c] = '.'
            elif grid[r][c] == 'B':
                bob_start = (r, c)
                grid[r][c] = '.'

    if not alice_start or not bob_start:
        return

    # BFS for Alice
    dist_a = [[float('inf')] * C for _ in range(R)]
    dist_a[alice_start[0]][alice_start[1]] = 0
    queue_a = deque([alice_start])

    dr = [0, 0, 1, -1]
    dc = [1, -1, 0, 0]

    while queue_a:
        r, c = queue_a.popleft()
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if 0 <= nr < R and 0 <= nc < C:
                cell = grid[nr][nc]
                if cell != '#' and cell != 'b': # Alice can't walk on 'b'
                    if dist_a[nr][nc] == float('inf'):
                        dist_a[nr][nc] = dist_a[r][c] + 1
                        queue_a.append((nr, nc))

    # BFS for Bob
    dist_b = [[float('inf')] * C for _ in range(R)]
    dist_b[bob_start[0]][bob_start[1]] = 0
    queue_b = deque([bob_start])

    while queue_b:
        r, c = queue_b.popleft()
        for i in range(4):
            nr, nc = r + dr[i], c + dc[i]
            if 0 <= nr < R and 0 <= nc < C:
                cell = grid[nr][nc]
                if cell != '#' and cell != 'a': # Bob can't walk on 'a'
                    if dist_b[nr][nc] == float('inf'):
                        dist_b[nr][nc] = dist_b[r][c] + 1
                        queue_b.append((nr, nc))

    min_time = float('inf')
    for r in range(R):
        for c in range(C):
            da = dist_a[r][c]
            db = dist_b[r][c]
            if da != float('inf') and db != float('inf'):
                min_time = min(min_time, max(da, db))

    if min_time == float('inf'):
        print("-1")
    else:
        print(min_time)

if __name__ == "__main__":
    solve()
