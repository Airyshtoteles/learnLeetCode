# Multiplayer Loot Distribution

Difficulty: Hard — DP + Sorting + Game Theory

Two players (A then B) alternately pick items. A can only take even `rarity`, B can only take odd `rarity`. If a player has no valid items, they skip. Game ends when all items are taken. Return the maximum score difference `scoreA - scoreB` assuming optimal play.

## Approach (Greedy over Sorted Values)
Sort items by `value` descending. Simulate turns:
- If current player has any valid item, take the highest-valued valid item.
- Otherwise, skip.

Because each player's action doesn't change the set of valid items for the other except removing one item, and picks don't affect future validity constraints beyond removal, this greedy is optimal.

- Time: `O(n log n)`
- Space: `O(n)` to store items
