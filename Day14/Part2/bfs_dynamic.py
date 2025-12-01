from collections import deque
from typing import List, Tuple, Optional, Set

# Part 2 — BFS Traversal with Dynamic Portals
# Deterministic simulation of portal remapping every t steps.

Pos = Tuple[int, int]
Grid = List[List[str]]


def _collect_cells(maze: Grid):
    n = len(maze)
    starts: List[Pos] = []
    exits: List[Pos] = []
    portals: List[Pos] = []
    empties: List[Pos] = []
    for i in range(n):
        for j in range(len(maze[i])):
            c = maze[i][j]
            if c == 'S':
                starts.append((i, j))
            elif c == 'X':
                exits.append((i, j))
            elif c == 'P':
                portals.append((i, j))
            if c == 'E' or c == 'P':
                empties.append((i, j))
    return starts, exits, portals, empties


def _portals_for_phase(empties: List[Pos], pcount: int, phase: int) -> Set[Pos]:
    """Deterministic portal layout for a given phase index.
    We pick pcount cells from empties by a cyclic shift starting offset=phase.
    """
    if pcount <= 0 or not empties:
        return set()
    res = set()
    m = len(empties)
    for k in range(pcount):
        res.add(empties[(phase + k) % m])
    return res


def _teleport_destination(portals: List[Pos], current: Pos) -> Optional[Pos]:
    """Teleport to another portal deterministically: the next portal in list order.
    If only one portal exists or none, return None (no-op).
    If current is not in portals (due to mapping mismatch), treat as no-op.
    """
    if len(portals) <= 1:
        return None
    try:
        idx = portals.index(current)
    except ValueError:
        return None
    nxt = (idx + 1) % len(portals)
    if portals[nxt] == current:
        return None
    return portals[nxt]


def shortestPathWithPortals(maze: Grid, t: int) -> int:
    n = len(maze)
    starts, exits, base_portals, empties = _collect_cells(maze)
    if not starts or not exits:
        return -1
    S = starts[0]
    X = exits[0]
    pcount = len(base_portals)

    # BFS with simple 2D visited (Part 2 baseline). Portals remap by phase = steps // t.
    q = deque()
    q.append((S[0], S[1], 0))  # (x, y, steps)
    visited = [[False]*n for _ in range(n)]
    visited[S[0]][S[1]] = True

    dirs = [(1,0),(-1,0),(0,1),(0,-1)]

    while q:
        x, y, steps = q.popleft()
        if (x, y) == X:
            return steps

        phase = steps // t  # portals layout for this step window
        portals_set = _portals_for_phase(empties, pcount, phase)
        portals_list = sorted(list(portals_set))  # stable order

        for dx, dy in dirs:
            nx, ny = x + dx, y + dy
            if not (0 <= nx < n and 0 <= ny < n):
                continue
            cell = maze[nx][ny]
            if cell == 'W':
                continue

            tx, ty = nx, ny
            # If destination is a portal under current layout, teleport instantly (no extra step)
            if (nx, ny) in portals_set:
                dest = _teleport_destination(portals_list, (nx, ny))
                if dest is not None:
                    tx, ty = dest

            if not visited[tx][ty]:
                visited[tx][ty] = True
                q.append((tx, ty, steps + 1))

    return -1


if __name__ == "__main__":
    maze = [
        ['S','E','P','W'],
        ['E','W','E','E'],
        ['E','P','W','E'],
        ['E','E','E','X']
    ]
    print(shortestPathWithPortals(maze, 3))
