import heapq
from typing import List, Tuple

goal = "123456780"

def serialize(board: List[List[int]]) -> str:
    return ''.join(str(x) for row in board for x in row)

def inversions(s: str) -> int:
    arr = [int(ch) for ch in s if ch != '0']
    inv = 0
    for i in range(len(arr)):
        for j in range(i+1, len(arr)):
            if arr[i] > arr[j]: inv += 1
    return inv

def solvable(s: str) -> bool:
    # 3x3 solvable iff inversion count even
    return inversions(s) % 2 == 0

pos = {str(v):( (v-1)//3, (v-1)%3 ) for v in range(1,9)}

def manhattan(s: str) -> int:
    # distance excluding blank
    dist = 0
    for i,ch in enumerate(s):
        if ch == '0':
            continue
        r, c = divmod(i, 3)
        gr, gc = pos[ch]
        dist += abs(r-gr) + abs(c-gc)
    return dist

def min_moves_8puzzle(board: List[List[int]]) -> int:
    start = serialize(board)
    if start == goal:
        return 0
    if not solvable(start):
        return -1
    start_h = manhattan(start)
    pq = [(start_h, 0, start)]  # (f=g+h, g, state)
    seen = {start: 0}
    dirs = [(-1,0),(1,0),(0,-1),(0,1)]
    while pq:
        f, g, s = heapq.heappop(pq)
        if s == goal:
            return g
        z = s.index('0')
        zr, zc = divmod(z, 3)
        for dr, dc in dirs:
            nr, nc = zr+dr, zc+dc
            if 0 <= nr < 3 and 0 <= nc < 3:
                nz = nr*3+nc
                lst = list(s)
                lst[z], lst[nz] = lst[nz], lst[z]
                t = ''.join(lst)
                ng = g + 1
                if t not in seen or ng < seen[t]:
                    seen[t] = ng
                    heapq.heappush(pq, (ng + manhattan(t), ng, t))
    return -1

if __name__ == "__main__":
    board = [[1,2,3],[4,0,6],[7,5,8]]
    print(min_moves_8puzzle(board))  # Expected 2
