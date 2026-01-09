#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

// Problem: Quantum Teleport Graph
// Deterministic strategy to reach Target.
// Input: N nodes, M edges.
// Each edge u -> v is a "move".
// But "Setiap node punya probabilitas teleport".
// Interpretation: From u, we can choose to go to v. But the system might teleport us to ANY neighbor of u?
// Or: The graph defines the transitions.
// "Kamu ingin strategi deterministik".
// This usually implies an "And-Or" graph or "Game against Nature".
// Let's assume:
// We are at u. We choose an action (edge).
// But wait, "Setiap node punya probabilitas teleport".
// Maybe we don't choose edge? Maybe we just choose "Move"?
// If we choose "Move", we land in one of the neighbors.
// If so, we can only win from u if ALL neighbors are winning states.
// But if we have multiple edges, maybe we choose which one to try?
// Let's assume the standard "Strong Preimage" or "Attractor" definition.
// We want to find the set W such that from any u in W, we can reach Target with probability 1 (or guarantee).
// If we have choices (actions), we pick the best action.
// If nature has choices (outcomes), we must win against all outcomes.
// Let's assume the input gives: u -> v1, u -> v2 ...
// And we have NO choice at a node other than "wait" or "go"?
// "Kamu ingin strategi".
// This implies we have choices.
// Maybe the graph is: u has edges to v1, v2...
// We choose an edge.
// But "probabilitas teleport" implies uncertainty.
// Maybe: We choose edge u->v. But we might land in v OR some other node?
// Or maybe: The node ITSELF teleports.
// Let's assume the "Game" interpretation:
// At node u, we choose a neighbor v.
// But the "teleport" might send us to any neighbor?
// If so, we can only win if ALL neighbors are winning.
// This makes the "choice" irrelevant (all choices lead to same set of possible outcomes?).
// Let's assume the input format is:
// N nodes. M directed edges.
// From u, we can choose to traverse any outgoing edge (u, v).
// BUT, "Setiap node punya probabilitas teleport".
// Maybe this means: After we arrive at v, we might be teleported?
// Or: When we are at u, before we move, we might be teleported?
// Let's go with the "All Neighbors" interpretation (Worst Case).
// We can reach Target from u if for SOME action, ALL outcomes lead to W.
// If the only action is "Move", and "Move" leads to {v1, v2...}, then we need {v1, v2...} subset W.
// If we have multiple actions (e.g. edges are distinct actions), then we need EXISTS action such that ALL outcomes in W.
// But usually in simple graph inputs, edges are just u->v.
// Does u->v mean "Action 1 leads to v"?
// If so, it's deterministic.
// "Setiap node punya probabilitas teleport".
// Maybe the graph represents the teleport links?
// i.e. u -> v means "If you are at u, you might teleport to v".
// And we have a "Control" action?
// "Kamu ingin strategi".
// Maybe we can choose to "Stay" or "Teleport"?
// Or maybe we can choose *which* teleport link to follow?
// If we can choose, it's just BFS.
// If we can't choose, it's "All Neighbors".
// Given "Hint: worst-case reachability + absorbing set", it strongly suggests "All Neighbors".
// i.e. We are at u. Next state is ANY v such that u->v exists.
// We win if ALL v are in W.
// Algorithm:
// W = {Target}
// Reverse graph R.
// Count out-degree of each node in original graph.
// Maintain "safe_degree" for each node (how many neighbors are in W).
// If safe_degree[u] == out_degree[u], then u is safe. Add to W.
// Propagate backwards.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> adj(N);
    vector<vector<int>> rev_adj(N);
    vector<int> out_degree(N, 0);

    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        out_degree[u]++;
    }

    int Start, Target;
    cin >> Start >> Target;

    if (Start == Target) {
        cout << "Possible" << endl;
        return 0;
    }

    // Winning set
    vector<bool> winning(N, false);
    vector<int> safe_edges(N, 0);
    queue<int> q;

    // Target is winning
    winning[Target] = true;
    q.push(Target);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : rev_adj[u]) {
            if (winning[v]) continue;
            
            safe_edges[v]++;
            if (safe_edges[v] == out_degree[v]) {
                winning[v] = true;
                q.push(v);
            }
        }
    }

    if (winning[Start]) {
        cout << "Possible" << endl;
    } else {
        cout << "Impossible" << endl;
    }

    return 0;
}
