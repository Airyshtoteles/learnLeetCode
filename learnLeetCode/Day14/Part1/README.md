# Day 14 — Part 1: Parse the Maze

Goal: Extract coordinates for 'S' (start), 'X' (exit), and all 'P' (portals) from an n x n grid.

## Python
Functions:
- `find_positions(maze, target) -> List[Tuple[int,int]]`
- `find_single(maze, target) -> Optional[Tuple[int,int]]`

Run the quick demo:
```
python parse_maze.py
```

## C++
Functions:
- `vector<pair<int,int>> findPositions(const vector<vector<char>> &maze, char target);`
- `optional<pair<int,int>> findSingle(const vector<vector<char>> &maze, char target);`

Build & run (example):
```
g++ -std=c++17 -O2 parse_maze.cpp -o parse_maze
./parse_maze
```

Notes:
- Works with rectangular grids.
- Returns empty list or null/None if not found.
