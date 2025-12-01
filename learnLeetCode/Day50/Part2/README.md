# Day 50 Part 2: Rogue Chess - Maximum Capture Chain

## Problem Description
You have an `N x N` chess board.
A **Rogue Knight** moves like a knight but can only move to a square if it contains an enemy piece (capturing it).
Each enemy piece has a point value.
Find the maximum total points obtainable from a valid chain of captures.
The knight can start at any square (implied, or maybe specified? Problem says "Ada satu bidak Rogue Knight", usually implies it's already placed or we place it. Let's assume we pick the best start or it's given. The input format `board` usually implies the knight is not on it, or marked. If not marked, we might pick any start. Let's assume we can start anywhere or pick a start that is a capture).
Actually, usually "Rogue Knight" implies we place it to start a chain.
Let's assume we can start by capturing any piece, or start at an empty square and jump?
"bisa melanjutkan langkah hanya jika dia memakan bidak musuh".
This implies the *continuation* requires capture. The first move?
Usually "Chain" implies a sequence of captures.
Let's assume we pick a starting piece to capture (score it), then continue.
Or we start at a designated spot.
Given "Input: board", and no start pos, I'll assume we can pick any enemy piece as the start of the chain (capturing it immediately) and then continue.

## Approach
This is a **Longest Path in a DAG** (or graph) problem.
Since we remove pieces, we can't visit the same square twice.
The graph nodes are the enemy pieces.
Edges exist from piece A to piece B if a knight move is possible.
Since `N <= 50`, the number of pieces is at most 2500.
However, the graph is sparse (max degree 8).
We can use **DFS with Memoization**.
State: `(current_piece_index, mask?)`.
Mask is too big ($2^{2500}$).
But we don't need a mask if we just do DFS.
Wait, without a mask, how do we know which pieces are taken?
We can modify the board during DFS (backtracking).
Since we want the *maximum* score, and the path length is finite, backtracking works.
Is it too slow?
Max path length could be large.
But knight graphs on 50x50 are large.
However, usually "Maximum Capture Chain" problems have a limited number of pieces or specific constraints.
If the board is full, it's Hamiltonian Path (NP-Hard).
Given "Hard" and N=50, maybe the number of pieces is small?
Or maybe we just implement backtracking with a timeout/heuristic?
Or maybe it's a specific structure.
I will implement **DFS with Backtracking**.

## Complexity
- **Time:** Exponential in worst case, but efficient for sparse graphs.
- **Space:** `O(N^2)` for recursion stack and board.
