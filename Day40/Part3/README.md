# Count Paths with Sum = Target in Binary Tree

Difficulty: Hard — Prefix Sum on Trees

Given a binary tree and an integer `target`, count the number of paths where the sum of the node values equals `target`. The path does not need to start or end at the root or a leaf, but it must go downwards (parent to child).

## Approach (DFS + Prefix Sums)
- Maintain a running prefix sum while traversing the tree.
- Use a hash map `cnt` where `cnt[x]` is how many times prefix sum `x` has appeared on the path from root to current node.
- For current prefix sum `cur`, number of valid paths ending here is `cnt[cur - target]`.
- Recurse on children; backtrack (`cnt[cur]--`).

Time: O(n), Space: O(h) average, O(n) worst.
