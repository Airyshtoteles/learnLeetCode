# Day 45 Part 8: Memory-Corruption Tetris

## Problem Description

You are given a sequence of Tetris pieces (fixed orientation).
*   **Board:** Width $W$, Height $H$.
*   **Input:** Sequence of piece types (e.g., 'I', 'O', 'T'...).
*   **Action:** For each piece, choose a column to drop it.
*   **Mechanic:**
    *   Pieces fall until they hit the ground or another block.
    *   **Line Clear:** If a row is completely full, it is cleared (removed). Blocks above fall down.
    *   **Memory Corruption:** Whenever a row is cleared, **one additional row** above it (if any exist) is also cleared.
        *   "Above" means higher y-coordinate (assuming 0 is bottom).
        *   "Random" in problem description, but "Maximize" in goal implies we consider the **Best Case** scenario (we choose which row above to clear).
*   **Goal:** Maximize the total number of cleared rows (normal + corrupted).

## Algorithm: Beam Search

Since the state space is large (Grid configuration), we cannot explore all possibilities.
We use **Beam Search** to keep the top $K$ most promising states at each step.

### State
`State = (Grid, Score)`
*   `Grid`: A tuple of tuples representing the board (0 for empty, 1 for filled).
*   `Score`: Total lines cleared so far.

### Transitions
For the current piece $P$:
1.  Try all valid columns $c$ where $P$ fits.
2.  Simulate drop.
3.  Check for full lines.
4.  If lines are full:
    *   Remove full lines.
    *   For each removed line, trigger "Corruption":
        *   Choose a row above to remove. (Branching factor increases here).
        *   To keep it manageable, maybe we just remove the *lowest* non-empty row above? Or the one that creates the best future?
        *   For "Best Case", we should branch on which row to corrupt.
        *   If multiple lines clear at once, we get multiple corruptions.
5.  Update Grid and Score.
6.  Keep top $K$ states based on Score (and maybe heuristic like "low pile height").

### Heuristic for Beam Search
Sort states by:
1.  Score (Descending).
2.  Max Height (Ascending) - lower is better.
3.  Holes (Ascending) - fewer holes is better.

### Implementation Details
*   Width: 6 (Small enough for simulation).
*   Height: 10-15.
*   Beam Width $K$: 50-100.
*   Pieces: Standard shapes.

```python
shapes = {
    'I': [[1, 1, 1, 1]],
    'O': [[1, 1], [1, 1]],
    'T': [[0, 1, 0], [1, 1, 1]],
    # ... etc
}
```
