# Day 30 — Part 2: Stone Game VIII

Problem (LeetCode 1872): Given stones, each move must take at least the first two stones and replace them with their sum; players alternate, maximizing score difference (Alice − Bob). Return the optimal difference.

Key idea:
- Work with prefix sums s[i] = sum(stones[0..i]). Any move that takes first i+1 stones scores s[i]. After the move, the game state for the opponent is effectively “starting from i+1”.
- Let dfs(i) be the maximum score difference the current player can achieve when they can choose to take up to index i (or skip it and let the opponent decide from i+1).
- Recurrence: dfs(i) = max(dfs(i+1), s[i] − dfs(i+1)). Base: when i ≥ n−1, dfs(i) = s[n−1]. Answer is dfs(1) (since the first move must take at least 2 stones).

Complexity:
- O(n) time and O(n) space with memoization (or bottom-up).

Files:
- stone_game_viii.py — Python implementation (memoized).
- stone_game_viii.cpp — C++17 implementation.
