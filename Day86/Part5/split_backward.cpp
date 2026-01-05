#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Problem: Player That Splits Backward
// Graph.
// Rule: From node u, player splits to ALL parent nodes (v such that v -> u).
// Goal: Determine if Target is reachable from Start using this movement.
// Strategy: This is equivalent to Reachability in the Reverse Graph (Transpose Graph).
// We check if there is a path from Start to Target in G^T.
// Or path from Target to Start in G?
// Wait. "Posisi pemain bercabang ke semua parent node".
// Start at S. Next step: Parents(S).
// So we are traversing edges backwards.
// We want to know if Target is in the set of reachable nodes.
// So: Path Start -> ... -> Target in Reverse Graph.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> rev_adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        // Edge u -> v.
        // We want to traverse v -> u.
        rev_adj[v].push_back(u);
    }

    int Start, Target;
    cin >> Start >> Target;

    // BFS from Start in Reverse Graph
    queue<int> q;
    q.push(Start);
    vector<bool> visited(N + 1, false);
    visited[Start] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == Target) {
            cout << "Possible" << endl;
            return 0;
        }

        for (int v : rev_adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
