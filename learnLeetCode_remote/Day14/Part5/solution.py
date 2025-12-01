from collections import deque
from typing import List, Tuple, Optional

Pos = Tuple[int,int]
Grid = List[List[str]]

class Solution:
    def minStepsToExit(self, maze: Grid, t: int) -> int:
        n = len(maze)
        S = None
        X = None
        initial_portals: List[Pos] = []
        empty_cells: List[Pos] = []  # only 'E' cells for remaps
        for i in range(n):
            for j in range(len(maze[i])):
                c = maze[i][j]
                if c == 'S':
                    S = (i, j)
                elif c == 'X':
                    X = (i, j)
                if c == 'P':
                    initial_portals.append((i,j))
                if c == 'E':
                    empty_cells.append((i,j))
        if S is None or X is None:
            return -1
        pcount = len(initial_portals)

        def portals_for_phase(phase: int):
            # Phase 0: portals are at their initial 'P' positions
            if phase == 0:
                return sorted(list(initial_portals))
            # Subsequent phases: remap to 'E' cells only
            if pcount <= 0 or not empty_cells:
                return []
            m = len(empty_cells)
            sel = [empty_cells[(phase + k) % m] for k in range(pcount)]
            sel.sort()
            return sel

        def teleport(plist: List[Pos], current: Pos) -> Optional[Pos]:
            if len(plist) <= 1:
                return None
            try:
                i = plist.index(current)
            except ValueError:
                return None
            j = (i + 1) % len(plist)
            if plist[j] == current:
                return None
            return plist[j]

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
            plist = portals_for_phase(phase)
            pset = set(plist)

            for dx, dy in dirs:
                nx, ny = x + dx, y + dy
                if not (0 <= nx < n and 0 <= ny < n):
                    continue
                if maze[nx][ny] == 'W':
                    continue
                tx, ty = nx, ny
                if (nx, ny) in pset:
                    dest = teleport(plist, (nx, ny))
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
    print(Solution().minStepsToExit(maze, 3))  # Expected 7 in prompt example
