from collections import deque
from typing import List, Tuple

def min_moves_with_portals(grid: List[str]) -> int:
    n = len(grid)
    grid2 = [list(row) for row in grid]
    start = target = None
    portals = {}
    for r in range(n):
        for c in range(len(grid2[r])):
            ch = grid2[r][c]
            if ch == 'S':
                start = (r, c)
            elif ch == 'T':
                target = (r, c)
            elif 'A' <= ch <= 'Z':
                portals.setdefault(ch, []).append((r, c))
    if start is None or target is None:
        return -1

    # Build portal mapping to paired coordinates
    tele = {}
    for ch, lst in portals.items():
        if len(lst) == 2:
            a, b = lst
            tele[a] = b
            tele[b] = a
        else:
            # If invalid (not exactly two), ignore as normal cell
            pass

    def inb(r,c):
        return 0 <= r < n and 0 <= c < len(grid2[r])

    sr, sc = start
    tr, tc = target
    q = deque([(sr, sc, 0)])
    vis = set([(sr, sc)])

    while q:
        r, c, d = q.popleft()
        if (r, c) == (tr, tc):
            return d
        for dr, dc in ((1,0),(-1,0),(0,1),(0,-1)):
            nr, nc = r + dr, c + dc
            if not inb(nr, nc):
                continue
            if grid2[nr][nc] == '#':
                continue
            # If stepping onto a portal, teleport instantly to its pair
            pr, pc = nr, nc
            ch = grid2[nr][nc]
            if 'A' <= ch <= 'Z' and (nr, nc) in tele:
                pr, pc = tele[(nr, nc)]
            if (pr, pc) in vis:
                continue
            vis.add((pr, pc))
            q.append((pr, pc, d + 1))
    return -1

if __name__ == "__main__":
    grid = [
        "S.A",
        ".#A",
        "..T"
    ]
    print(min_moves_with_portals(grid))  # Expected 4
