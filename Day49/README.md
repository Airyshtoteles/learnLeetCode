# Day 49: Advanced Algorithmic Challenges

Today's focus was on solving 5 "Hard" algorithmic problems involving complex state transitions, linear algebra, modular arithmetic, dynamic programming, and physics simulations.

## Problems

### Part 1: Game of Dissonant Mirrors
- **Concept:** BFS with Global State Flip.
- **Description:** Navigating a grid where landing on a '1' flips the entire grid's values (0->1, 1->0).
- **Solution:** BFS with state `(row, col, grid_parity)`.

### Part 2: Arcane Fusion Battle
- **Concept:** Linear Basis (Gaussian Elimination over GF(2)).
- **Description:** Finding the maximum XOR subset sum from a list of numbers.
- **Solution:** Construct a Linear Basis and greedily maximize the result.

### Part 3: Time-Shifted Labyrinth
- **Concept:** BFS with Modular Arithmetic.
- **Description:** A grid where cells are blocked periodically based on time modulo K.
- **Solution:** BFS with state `(row, col, time % K)` for visitation, tracking total time.

### Part 4: Rune Compression Arena
- **Concept:** Dynamic Programming (Run-Length Encoding).
- **Description:** Compressing a string by deleting at most `k` characters to minimize RLE length.
- **Solution:** DP state `dp[index][k_left]`, iterating forward to group identical characters.

### Part 5: Gravity Flip Duel
- **Concept:** Shortest Path (0-1 BFS) with Physics.
- **Description:** Navigating a grid with gravity. Walking is free, flipping gravity costs energy.
- **Solution:** 0-1 BFS with state `(row, col, gravity_direction)`, simulating falling mechanics.

## Structure
Each part has its own directory with:
- `README.md`: Detailed problem analysis.
- `*.py`: Python solution.
- `*.cpp`: C++ solution.
