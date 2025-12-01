# Shortest Path with Alternating Colors

Difficulty: Medium/Hard — BFS on (node, color) States

Given a directed graph with red and blue edges and `n` nodes labeled `0..n-1`, return the shortest distance from node `0` to every node such that the path alternates colors between red and blue at each step. If a node is unreachable, return `-1` for that node.

## Approach (BFS with Color State)
- Build adjacency lists for red and blue edges.
- BFS over states `(node, lastColor)`, where lastColor ∈ {red, blue, none for start}.
- From `(u, lastColor)`, traverse edges of the opposite color.
- Track visited by `(node, lastColor)` to avoid revisits; maintain distance per state and take min per node.

Time: O(n + r + b), Space: O(n + r + b).
