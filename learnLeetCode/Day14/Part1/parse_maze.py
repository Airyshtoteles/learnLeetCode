from typing import List, Tuple, Optional

# Part 1 — Parse the Maze
# Write helper functions to locate 'S', 'X', and collect any target positions like 'P'.

Pos = Tuple[int, int]
Grid = List[List[str]]

def find_positions(maze: Grid, target: str) -> List[Pos]:
    """Return all (row, col) positions where maze[row][col] == target.

    Assumes maze is a rectangular list of lists of single-character strings.
    """
    n = len(maze)
    res: List[Pos] = []
    for i in range(n):
        row = maze[i]
        for j in range(len(row)):
            if row[j] == target:
                res.append((i, j))
    return res


def find_single(maze: Grid, target: str) -> Optional[Pos]:
    """Return the first position of target if present, else None."""
    n = len(maze)
    for i in range(n):
        row = maze[i]
        for j in range(len(row)):
            if row[j] == target:
                return (i, j)
    return None


if __name__ == "__main__":
    maze = [
        ['S','E','P','W'],
        ['E','W','E','E'],
        ['E','P','W','E'],
        ['E','E','E','X']
    ]
    print("Positions of 'P':", find_positions(maze, 'P'))
    print("Start 'S':", find_single(maze, 'S'))
    print("Exit  'X':", find_single(maze, 'X'))
