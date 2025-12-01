# Day 45 Part 2: Multi-Layer Domino Collapse

## Problem Description

You have 3 layers of dominoes, each an $N \times M$ grid.
*   `grid[k][i][j] == 1` means there is a domino.
*   **Propagation Rules:**
    1.  **Horizontal:** If a domino falls, all its orthogonal neighbors in the same layer fall.
    2.  **Vertical:** If a domino at $(i, j)$ falls in any layer, the dominoes at $(i, j)$ in all other layers also fall (if they exist).
*   **Action:** You can manually push up to **2** dominoes.
*   **Goal:** Maximize the total number of fallen dominoes.

## Algorithm: Connected Components

Since the propagation rules are transitive (A triggers B, B triggers C $\implies$ A triggers C), the set of dominoes that fall together forms a **Connected Component** in the dependency graph.

### Graph Construction
*   **Nodes:** Every cell $(k, i, j)$ where `grid[k][i][j] == 1`.
*   **Edges:**
    *   $(k, i, j) \leftrightarrow (k, ni, nj)$ for neighbors $(ni, nj)$.
    *   $(k, i, j) \leftrightarrow (k', i, j)$ for all layers $k, k'$.

### Steps
1.  Initialize a `visited` array for all layers.
2.  Iterate through all cells. If a cell has a domino and is not visited:
    *   Start a BFS/DFS to find the size of the Connected Component (CC).
    *   Mark all reachable nodes as visited.
    *   Store the size of the CC.
3.  Collect all CC sizes.
4.  Sort sizes in descending order.
5.  Result is the sum of the top 2 sizes (or top 1 if only 1 CC exists).

## Complexity
*   **Time:** $O(L \cdot N \cdot M)$ where $L=3$.
*   **Space:** $O(L \cdot N \cdot M)$ for visited array.
