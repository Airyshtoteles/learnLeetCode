from typing import List

BASE = 100001  # > max grid value (<= 1e4)

def count_darkened(grid: List[List[int]]) -> int:
    n = len(grid)
    if n == 0:
        return 0

    H = V = I = 0

    # Row-wise: horizontal coverage, mark covered cells by adding BASE
    for i in range(n):
        rem = 0
        for j in range(n):
            val = grid[i][j] % BASE
            if rem > 0:
                H += 1
                grid[i][j] += BASE  # mark horizontal cover
                rem -= 1
            # start/extend segment from current cell
            if val > rem:
                rem = val
    
    # Col-wise: vertical coverage, compute intersection using mark
    for j in range(n):
        rem = 0
        for i in range(n):
            val = grid[i][j] % BASE
            if rem > 0:
                V += 1
                if grid[i][j] >= BASE:  # horizontally covered
                    I += 1
                rem -= 1
            if val > rem:
                rem = val

    return H + V - I

if __name__ == "__main__":
    grid = [[1,2], [3,1]]
    print(count_darkened(grid))  # Expected 6
