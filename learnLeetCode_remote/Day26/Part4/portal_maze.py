from collections import deque
from typing import List, Tuple

def min_steps(maze: List[str]) -> int:
    n, m = len(maze), len(maze[0]) if maze else 0
    if n == 0 or m == 0:
        return -1
    portals = {}
    start = end = None
    for i in range(n):
        for j in range(m):
            c = maze[i][j]
            if c == 'S':
                start = (i, j)
            elif c == 'T':
                end = (i, j)
            elif 'A' <= c <= 'Z':
                portals.setdefault(c, []).append((i, j))
    if start is None or end is None:
        return -1

    def teleport(i: int, j: int) -> Tuple[int,int]:
        c = maze[i][j]
        if not ('A' <= c <= 'Z'): return (i,j)
        lst = portals.get(c, [])
        if len(lst) == 2:
            a, b = lst
            return b if (i,j) == a else a
        # single or more than 2: stay in place (robustness)
        return (i,j)

    q = deque([start])
    dist = {start: 0}
    DIRS = [(-1,0),(1,0),(0,-1),(0,1)]
    while q:
        x, y = q.popleft()
        if (x, y) == end:
            return dist[(x,y)]
        for dx, dy in DIRS:
            nx, ny = x + dx, y + dy
            if 0 <= nx < n and 0 <= ny < m and maze[nx][ny] != '#':
                if maze[nx][ny] == '.' or maze[nx][ny] in 'ST':
                    nxt = (nx, ny)
                else:
                    # letter: step into it then teleport to its pair
                    nxt = teleport(nx, ny)
                if nxt not in dist:
                    dist[nxt] = dist[(x,y)] + 1
                    q.append(nxt)
    return -1

if __name__ == "__main__":
    maze = [
        "S.A#",
        ".#A.",
        ".#..",
        "...T"
    ]
    print(min_steps(maze))  # Expected 7
