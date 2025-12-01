# Day 51 Part 4: Virus Containment

## Problem Description
A computer network is under attack by a self-replicating virus.
The network is represented as a graph where nodes are servers and edges are connections.

Some servers are already **Infected**.
Some servers are **Critical** and must be protected at all costs.
The virus can spread from any infected server to any adjacent server via connections.

Your task is to **remove the minimum number of connections** (edges) to completely isolate the Critical servers from the Infected servers.
If it is impossible to save all Critical servers (e.g., one is already infected), return -1.

## Input Format
- `n`: Number of servers (0 to n-1).
- `connections`: List of pairs `(u, v)` representing edges.
- `infected`: List of IDs of infected servers.
- `critical`: List of IDs of critical servers.

## Constraints
- $n \le 100$
- Number of connections $\le 500$
- A server cannot be both Infected and Critical.

## Strategy
This is a classic **Min-Cut** problem, which can be solved using the **Max-Flow Min-Cut Theorem**.

1. Construct a flow network:
   - Create a super-source $S$ and a super-sink $T$.
   - For each server in `infected`, add an edge from $S$ to the server with capacity $\infty$.
   - For each server in `critical`, add an edge from the server to $T$ with capacity $\infty$.
   - For each original connection `(u, v)`, add undirected edges between $u$ and $v$ with capacity 1.
     - Since max flow is directed, add directed edges $u \to v$ and $v \to u$, both with capacity 1.
2. Compute the **Max Flow** from $S$ to $T$.
   - The value of the max flow is equal to the minimum capacity of a cut that separates $S$ from $T$.
   - Since internal edges have capacity 1, this corresponds to the minimum number of edges to remove.
   - Since $S$-edges and $T$-edges have $\infty$ capacity, they will never be part of the min-cut (unless a node is both infected and critical, which is impossible by constraints).
3. Algorithm: **Edmonds-Karp** or **Dinic's Algorithm**.
   - Since $N$ is small (100), Edmonds-Karp (BFS based) is sufficient.

## Complexity
- Edmonds-Karp: $O(V E^2)$.
- Here $V \approx 100$, $E \approx 500 + 200$.
- Fast enough.

