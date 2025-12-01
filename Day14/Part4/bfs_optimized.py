from collections import deque
from typing import List, Tuple, Optional, Set

# Part 4 — Optimization: Use visited[x][y][step % t] to avoid redundant revisits

Pos = Tuple[int, int]
Grid = List[List[str]]

def _collect_cells(maze: Grid):
    n = len(maze)
    S = None
    X = None
    portals = []
    empties = []
    for i in range(n):
        for j in range(len(maze[i])):
            c = maze[i][j]
            if c == 'S':
                S = (i, j)
            elif c == 'X':
                X = (i, j)
            if c == 'P':
                portals.append((i, j))
            if c == 'E' or c == 'P':
                empties.append((i, j))
    return S, X, portals, empties


def _portals_for_phase(empties: List[Pos], pcount: int, phase: int) -> List[Pos]:
    if pcount <= 0 or not empties:
        return []
    m = len(empties)
    sel = []
    for k in range(pcount):
        sel.append(empties[(phase + k) % m])
    sel.sort()
    return sel


def _teleport_destination(portals: List[Pos], current: Pos) -> Optional[Pos]:
    if len(portals) <= 1:
        return None
    try:
        i = portals.index(current)
    except ValueError:
        return None
    j = (i + 1) % len(portals)
    if portals[j] == current:
        return None
    return portals[j]


def shortestPathOptimized(maze: Grid, t: int) -> int:
    n = len(maze)
    S, X, base_portals, empties = _collect_cells(maze)
    if S is None or X is None:
        return -1
    pcount = len(base_portals)

    # visited with third dimension step%t
    visited = [[[False]*t for _ in range(n)] for __ in range(n)]
    q = deque()
    q.append((S[0], S[1], 0))
    visited[S[0]][S[1]][0 % t] = True

    dirs = [(1,0),(-1,0),(0,1),(0,-1)]

    while q:
        x, y, steps = q.popleft()
        if (x, y) == X:
            return steps
        phase = steps // t
        cur_mod = steps % t
        plist = _portals_for_phase(empties, pcount, phase)
        pset = set(plist)

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            if not (0 <= nx < n and 0 <= ny < n):
                continue
            if maze[nx][ny] == 'W':
                continue

            tx, ty = nx, ny
            if (nx, ny) in pset:
                dest = _teleport_destination(plist, (nx, ny))
                if dest is not None:
                    tx, ty = dest

            nsteps = steps + 1
            nmod = nsteps % t
            if not visited[tx][ty][nmod]:
                visited[tx][ty][nmod] = True
                q.append((tx, ty, nsteps))

    return -1


if __name__ == "__main__":
    maze = [
        ['S','E','P','W'],
        ['E','W','E','E'],
        ['E','P','W','E'],
        ['E','E','E','X']
    ]
    print(shortestPathOptimized(maze, 3))
