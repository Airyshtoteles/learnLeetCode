# Day 52 Part 2: Necromancer's Minion Network

## Problem Description
The Necromancer has a vast network of minions. The network is represented as a directed graph where a directed edge $u \to v$ means minion $u$ can send a message to minion $v$.

The Necromancer wants to ensure that the network is **Strongly Connected**. This means that for any two minions $A$ and $B$, there is a path from $A$ to $B$ AND a path from $B$ to $A$.

Currently, the network might not be strongly connected.
Your task is to find the **minimum number of new edges** (communication channels) that need to be added to the graph to make it strongly connected.

## Input Format
- `n`: Number of minions (0 to n-1).
- `connections`: List of pairs `(u, v)` representing directed edges.

## Constraints
- $n \le 5000$
- $connections \le 10000$

## Strategy
This problem can be solved by analyzing the **Strongly Connected Components (SCCs)** of the graph.

1. **Find SCCs**: Use **Kosaraju's Algorithm** or **Tarjan's Algorithm**.
   - Kosaraju's uses two DFS passes and the **Reverse Graph**.
   - Pass 1: Compute finish times (Topological sort order).
   - Pass 2: DFS on the Transpose Graph (edges reversed) in decreasing order of finish times to extract SCCs.

2. **Build Condensation Graph**:
   - Treat each SCC as a single node.
   - Add a directed edge from SCC $U$ to SCC $V$ if there is an edge in the original graph from some node in $U$ to some node in $V$.
   - The resulting Condensation Graph is a **Directed Acyclic Graph (DAG)**.

3. **Analyze DAG**:
   - To make a DAG strongly connected (which effectively makes the whole graph strongly connected), we need to add edges to close the cycles.
   - Count the number of **Source SCCs** (In-Degree = 0) in the DAG. Let this be $S$.
   - Count the number of **Sink SCCs** (Out-Degree = 0) in the DAG. Let this be $T$.
   - The minimum edges needed is $\max(S, T)$.
   - **Exception**: If the graph is already strongly connected (1 SCC), the answer is 0.

## Complexity
- Finding SCCs: $O(V + E)$.
- Building Condensation Graph: $O(V + E)$.
- Counting Sources/Sinks: $O(V_{scc} + E_{scc})$.
- Total: Linear in terms of graph size.

