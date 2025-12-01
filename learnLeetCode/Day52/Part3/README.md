# Day 52 Part 3: Celestial Platform Shifter

## Problem Description
You are navigating a celestial obstacle course where gravity is not constant.
The course is an $N \times M$ grid.
- `.` : Empty space
- `#` : Wall/Platform
- `S` : Start
- `E` : End

**Physics Rules:**
1. **Gravity**: There is always a gravity direction $G$ (Initially **Down**).
   - Down: $(1, 0)$
   - Up: $(-1, 0)$
   - Left: $(0, -1)$
   - Right: $(0, 1)$
2. **Falling**: If the cell immediately in the direction of gravity is Empty (`.`, `S`, `E`), you **must** fall into it. This takes 1 time unit. You cannot perform other actions while falling.
3. **Grounded**: If the cell in the direction of gravity is a Wall (`#`) or bounds, you are **Grounded**.
4. **Actions (Only when Grounded)**:
   - **Walk**: Move 1 step perpendicular to gravity. Takes 1 time unit.
     - If $G$ is Down/Up, you can move Left/Right.
     - If $G$ is Left/Right, you can move Up/Down.
     - You cannot walk into a wall.
   - **Gravity Shift**: Change $G$ to any of the 4 directions. Takes 1 time unit. Consumes 1 **Flip Charge**.
     - You start with $K$ Flip Charges.

**Goal:**
- Reach the `E`xit in minimum time units.
- If impossible, return -1.

## Input Format
- `grid`: List of strings.
- `K`: Max gravity flips allowed.

## Constraints
- $N, M \le 50$
- $K \le 100$

## Strategy
This is a shortest-path problem on a graph.
**State**: $(r, c, g, flips)$
- $r, c$: Position
- $g$: Gravity Direction (0:D, 1:U, 2:L, 3:R)
- $flips$: Flips remaining

**Transitions**:
1. Check if "Falling" (cell in direction $G$ is empty).
   - If yes, next state is $(r+dr, c+dc, g, flips)$. Cost 1.
   - Note: Falling is mandatory. If you are falling, you *cannot* walk or shift.
   - However, can you shift *while* falling? The problem says "Actions (Only when Grounded)". So no.
2. If "Grounded":
   - **Walk**: Try moving in perpendicular directions.
     - Check if destination is valid (not wall).
     - Next state: $(r', c', g, flips)$. Cost 1.
   - **Shift**: Try changing $G$ to $g'$.
     - If $flips > 0$.
     - Next state: $(r, c, g', flips-1)$. Cost 1.
     - Note: After shifting, you might immediately start falling in the new direction in the *next* turn.

**Algorithm**: BFS (since edge weights are all 1).

## Complexity
- States: $N \times M \times 4 \times K$.
- $50 \times 50 \times 4 \times 100 \approx 1,000,000$.
- Feasible.

