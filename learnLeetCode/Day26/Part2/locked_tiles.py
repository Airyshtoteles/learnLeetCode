from collections import deque
from typing import List, Tuple

GOAL = tuple(range(1,16)) + (0,)
GOAL_STR = ''.join('{:X}'.format(x) for x in GOAL)

# neighbors for index 0..15 in 4x4 grid
NEI = {
    0: [1,4], 1: [0,2,5], 2: [1,3,6], 3: [2,7],
    4: [0,5,8], 5: [1,4,6,9], 6: [2,5,7,10], 7: [3,6,11],
    8: [4,9,12], 9: [5,8,10,13], 10: [6,9,11,14], 11: [7,10,15],
    12: [8,13], 13: [9,12,14], 14: [10,13,15], 15: [11,14]
}

def serialize(board: List[List[int]]) -> str:
    flat = [x for row in board for x in row]
    return ''.join('{:X}'.format(x) for x in flat)

def deserialize(s: str) -> Tuple[int,...]:
    return tuple(int(ch, 16) for ch in s)

def inversion_count(arr: Tuple[int,...]) -> int:
    a = [x for x in arr if x != 0]
    inv = 0
    for i in range(len(a)):
        for j in range(i+1, len(a)):
            if a[i] > a[j]:
                inv += 1
    return inv

def solvable(key: str) -> bool:
    arr = deserialize(key)
    inv = inversion_count(arr)
    zero_idx = arr.index(0)  # 0..15, row = idx//4 (top=0)
    row_from_bottom = 4 - (zero_idx // 4)  # 1..4
    # standard 4x4 goal solvable condition
    return (inv + row_from_bottom) % 2 == 1


def min_moves(board: List[List[int]]) -> int:
    start = serialize(board)
    if start == GOAL_STR:
        return 0
    if not solvable(start):
        return -1
    q = deque([start])
    dist = {start: 0}
    while q:
        s = q.popleft()
        d = dist[s]
        arr = list(deserialize(s))
        z = arr.index(0)
        for nz in NEI[z]:
            b = arr[:]
            b[z], b[nz] = b[nz], b[z]
            ns = ''.join('{:X}'.format(x) for x in b)
            if ns not in dist:
                dist[ns] = d + 1
                if ns == GOAL_STR:
                    return d + 1
                q.append(ns)
    return -1


if __name__ == "__main__":
    board = [
        [1,2,3,4],
        [5,6,7,8],
        [9,10,11,12],
        [13,15,14,0]
    ]
    print(min_moves(board))  # Expected 2
