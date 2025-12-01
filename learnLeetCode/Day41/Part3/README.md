# Lexicographically Smallest K-Cover of a Graph

Level: Hard

We need a minimal-size set S of nodes such that every node has at least k neighbors inside S. If multiple minimal S, choose lexicographically smallest (sorted list).

## Feasibility
If any node has degree < k, impossible (return empty).
If k == 0, answer is empty set.

## Approximate Greedy (Heuristic)
The exact problem resembles a hitting constraint that is NP-hard (variant of minimum k-neighbor cover). We use a heuristic:
1. Filter nodes with degree < k → impossible.
2. Sort nodes by id ascending.
3. Maintain counts of selected neighbors for each node.
4. Iterate nodes in ascending order; tentatively include node v if there exists a node u (including v) for which selecting v helps reach k and still needed.
5. After pass, verify all nodes have ≥ k selected neighbors; if not, augment by adding remaining nodes (ascending) until constraints satisfied or no progress.
6. Return S (sorted). NOTE: Heuristic may over-select.

Complexity: O(n log n + m).

This provides a solution under given constraints though not guaranteed minimal; used here for illustration.
