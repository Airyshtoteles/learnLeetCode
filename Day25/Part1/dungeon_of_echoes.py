# The Dungeon of Echoes
# Assumptions:
# - You can move 4-directionally into cells that are not walls: 0 or 2.
# - Standing on a portal (2), you may teleport to any other portal; teleport cost is 1 step.
# - After each teleport, the echo destroys the source row and source column: all 0 in that row/col become 1 (walls). Portals (2) remain passable.
# Goal: shortest steps from (0,0) to (m-1,n-1), else -1. Use BFS on state (r,c,rowMask,colMask).
from collections import deque
from typing import List, Tuple

def shortest_path_dungeon(grid: List[List[int]]) -> int:
    m = len(grid); n = len(grid[0]) if m else 0
    if m == 0 or n == 0: return -1
    portals: List[Tuple[int,int]] = [(i,j) for i in range(m) for j in range(n) if grid[i][j] == 2]
    portal_set = set(portals)

    def is_blocked(i: int, j: int, rm: int, cm: int) -> bool:
        if grid[i][j] == 1: return True
        if grid[i][j] == 2: return False
        # grid[i][j] == 0
        if (rm >> i) & 1: return True
        if (cm >> j) & 1: return True
        return False

    start_blocked = is_blocked(0,0,0,0)
    target_blocked = is_blocked(m-1,n-1,0,0)
    if start_blocked or target_blocked: return -1

    dq = deque()
    dq.append((0,0,0,0,0))  # r,c,rowMask,colMask,dist
    seen = set([(0,0,0,0)])

    while dq:
        r,c,rm,cm,d = dq.popleft()
        if (r,c) == (m-1,n-1):
            return d
        # normal moves
        for dr,dc in ((1,0),(-1,0),(0,1),(0,-1)):
            nr, nc = r+dr, c+dc
            if 0 <= nr < m and 0 <= nc < n and not is_blocked(nr,nc,rm,cm):
                key = (nr,nc,rm,cm)
                if key not in seen:
                    seen.add(key)
                    dq.append((nr,nc,rm,cm,d+1))
        # teleport moves if standing on a portal
        if grid[r][c] == 2 and portals:
            new_rm = rm | (1 << r)
            new_cm = cm | (1 << c)
            for (pr,pc) in portals:
                if (pr,pc) == (r,c):
                    continue
                # landing on portal always allowed (portals immune)
                key = (pr,pc,new_rm,new_cm)
                if key not in seen:
                    seen.add(key)
                    dq.append((pr,pc,new_rm,new_cm,d+1))
    return -1

if __name__ == "__main__":
    grid = [
        [0,2,0],
        [1,0,0],
        [2,1,0]
    ]
    print(shortest_path_dungeon(grid))  # example ~ 4 under these rules
