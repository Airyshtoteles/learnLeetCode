# Day 58: Advanced Algorithmic Challenges

## 1. Dungeon Mirror Teleport
**Problem:**
Find minimum steps from 'S' to 'E' in a grid.
- '0': Floor
- '1': Wall
- 'M': Mirror Teleport (All 'M's are connected with 0 cost, but entering takes 1 step).
- 'S': Start
- 'E': Exit

**Input:**
Grid of chars.

**Output:**
Minimum steps.

## 2. Maximum Score from Exploding Gems
**Problem:**
Maximize score by destroying gems.
- Destroying gems[i] adds gems[i] to score.
- Neighbors i-1 and i+1 get gems[i] added to them.
- gems[i] is removed.

**Input:**
Array of integers.

**Output:**
Max score.

## 3. The Maze With Sliding Walls
**Problem:**
Navigate maze with sliding walls 'W'.
- Walls move right each turn (wrap around).
- Avoid walls.
- Find min steps S to E.

**Input:**
Grid of chars.

**Output:**
Min steps.

## 4. Multiplayer Turn-Based Battle
**Problem:**
Minimize turns to leave 1 survivor.
- n players with HP and ATK.
- Each turn, 1 player attacks another.
- Optimal strategy control.

**Input:**
HP array, ATK array.

**Output:**
Min turns.

## 5. Minimum Time to Clear Falling Blocks
**Problem:**
Tetris-like optimization.
- Minimize final height.
- Choose column/rotation for sequence of blocks.
- Rows clear.

**Input:**
Block sequence, W, H.

**Output:**
Min height.
