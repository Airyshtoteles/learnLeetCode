# Day 24 — Part 5: The Truth Chain

Definition: trust[a] = b means a trusts b. Master of Truth is someone who trusts nobody (outdegree 0) and everyone else trusts them transitively.

Approach:
- Build original and reversed graphs; track outdegrees in original.
- Candidates have outdegree 0. For each candidate c, BFS/DFS in the reversed graph starting at c; if we can reach all n nodes, then all others can reach c in the original graph.
- Return that candidate’s id (1-based), or -1 if none.

Complexity: O(n + m).

Files:
- truth_chain.py — Python implementation with sample.
- truth_chain.cpp — C++17 implementation.
