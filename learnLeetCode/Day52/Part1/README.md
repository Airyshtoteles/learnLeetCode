# Day 52 Part 1: Echo of the Mirror Boss

## Problem Description
You are exploring a cursed dungeon where your movements are mimicked by a Mirror Boss.
The dungeon is represented by an $N \times M$ grid.
- `.` : Empty floor
- `#` : Wall
- `P` : Player Start
- `B` : Boss Start
- `E` : Exit

You control the Player. When you make a move (Up, Down, Left, Right), the Boss attempts to move in the **opposite** direction (Down, Up, Right, Left).

**Movement Rules:**
1. If the Player tries to move into a wall, the Player stays in place.
2. If the Boss tries to move into a wall, the Boss stays in place.
3. The move happens simultaneously.

**Game Over:**
- If at any point (including the start or after a move) the Player and the Boss occupy the **same cell**, the Boss catches you, and you lose.

**Goal:**
- Find the minimum number of moves for the Player to reach the `E`xit without being caught by the Boss.
- If it's impossible, return -1.

## Input Format
- `grid`: List of strings representing the dungeon.

## Constraints
- $N, M \le 20$
- The grid contains exactly one 'P', one 'B', and one 'E'.

## Strategy
This is a shortest-path problem on a graph where the state is defined by the positions of both the Player and the Boss.
State: $(r_P, c_P, r_B, c_B)$.

We can use **Breadth-First Search (BFS)** to find the minimum steps.

1. **Initial State**: Find coordinates of 'P' and 'B'.
2. **Transitions**:
   - Try all 4 directions for Player: $\Delta P \in \{(-1, 0), (1, 0), (0, -1), (0, 1)\}$.
   - Corresponding Boss directions: $\Delta B \in \{(1, 0), (-1, 0), (0, 1), (0, -1)\}$.
   - Calculate new positions $(nr_P, nc_P)$ and $(nr_B, nc_B)$.
   - Handle walls: if new pos is wall, stay at old pos.
3. **Validity Check**:
   - If $(nr_P, nc_P) == (nr_B, nc_B)$, this state is invalid (Caught).
   - If state visited, skip.
4. **Termination**:
   - If grid[nr_P][nc_P] == 'E', return steps + 1.

## Complexity
- State space size: $(N \times M)^2$.
- For $20 \times 20$, states $\approx 400^2 = 160,000$.
- Edges per state: 4.
- BFS is efficient enough.

