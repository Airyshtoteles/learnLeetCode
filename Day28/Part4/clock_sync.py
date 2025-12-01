from typing import List

def min_presses(clocks: List[int], ops: List[List[int]]) -> int:
    n = len(clocks)
    m = len(ops)
    cur = clocks[:]
    best = [float('inf')]

    def apply_button(i: int, times: int):
        if times % 12 == 0:
            return
        t = times % 12
        for j in range(n):
            if ops[i][j]:
                cur[j] = (cur[j] + t) % 12

    def dfs(i: int, used: int):
        if used >= best[0]:
            return
        if i == m:
            if all(x == 0 for x in cur):
                best[0] = min(best[0], used)
            return
        # Try pressing button i from 0..11 times
        snapshot = cur[:]
        for t in range(12):
            apply_button(i, t)
            dfs(i+1, used + t)
            cur[:] = snapshot

    dfs(0, 0)
    return -1 if best[0] == float('inf') else best[0]

if __name__ == "__main__":
    # Example small case
    clocks = [3, 6, 9]
    ops = [
        [1,0,1],
        [0,1,1]
    ]
    print(min_presses(clocks, ops))
