# Day 52 Part 5: Forbidden Hex Arena

## Problem Description
You are navigating a Forbidden Arena laid out on a **Hexagonal Grid**.
The grid uses **Axial Coordinates** $(q, r)$.
- `.` : Empty hex
- `#` : Wall
- `S` : Start
- `E` : End
- `a`-`j` : Pressure Plates (IDs 0-9).
- `A`-`J` : Toggleable Barriers (IDs 0-9).

**Mechanics:**
1. **Movement**: From $(q, r)$, you can move to 6 neighbors:
   - $(q+1, r)$, $(q+1, r-1)$, $(q, r-1)$, $(q-1, r)$, $(q-1, r+1)$, $(q, r+1)$.
2. **Pressure Plates**: When you step on a plate with ID $k$ (e.g., 'a' is 0), it **toggles** the state of all Barriers with ID $k$ ('A').
   - Initially, all Barriers are **Closed** (act as Walls).
   - Toggling opens them (passable) or closes them.
   - The toggle happens immediately upon entering the hex.
3. **Barriers**: You can only pass through a Barrier 'A' if it is currently **Open**.
   - Note: If you are standing on a plate 'a', the barrier 'A' is Open. If you step off 'a' and step on another 'a', it toggles back to Closed?
   - Usually, plates are "Toggle Switches". Step on it -> Flip state.
   - State is persistent.
   - If you step on 'a' again, it flips 'A' back.

**Goal:**
- Reach `E` in minimum steps.

## Input Format
- `grid_map`: A dictionary or list representation. Since hex grids are hard to represent as 2D arrays directly without offset, we'll use a list of strings and assume "Odd-r" or "Axial" mapping?
- Let's use a **Hash Map** for the grid: `(q, r) -> char`.
- Input will be a list of tuples `(q, r, type)`.

## Constraints
- Number of hexes $\le 1000$.
- Number of switch types $\le 10$.

## Strategy
BFS on State Graph.
**State**: $(q, r, mask)$
- $q, r$: Position.
- $mask$: Bitmask of barrier states (0=Closed, 1=Open).
- Initial Mask: 0.

**Transitions**:
- Try 6 neighbors.
- If neighbor is Wall `#`: Invalid.
- If neighbor is Barrier `A` (ID $k$):
  - Check if $k$-th bit in mask is 1.
  - If yes, valid move. New state $(nq, nr, mask)$.
  - If no, invalid (blocked).
- If neighbor is Plate `a` (ID $k$):
  - Valid move.
  - New mask = $mask \oplus (1 \ll k)$.
  - New state $(nq, nr, new\_mask)$.
- If neighbor is Empty/Start/End:
  - Valid move. New state $(nq, nr, mask)$.

## Complexity
- States: $N \times 2^K$.
- $1000 \times 1024 \approx 10^6$.
- Feasible.

