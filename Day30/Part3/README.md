# Day 30 — Part 3: Stone Game IV

Problem (LeetCode 1510): Given n stones, players alternate removing a non-zero perfect square number of stones. Alice starts. Return whether Alice wins assuming optimal play.

Key idea:
- Classic impartial game DP: dp[i] = can the current player force a win with i stones?
- Transition: dp[i] = True if exists k with k^2 ≤ i such that dp[i − k^2] is False (i.e., we move to a losing state for the opponent); else False.

Complexity:
- O(n * sqrt(n)) time, O(n) space.

Files:
- stone_game_iv.py — Python implementation.
- stone_game_iv.cpp — C++17 implementation.
