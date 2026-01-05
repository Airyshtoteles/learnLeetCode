#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Problem: Economy With No Stable State
// Graph.
// Rule: If state is stable (unchanged after action), you lose.
// This means we cannot traverse self-loops (u -> u).
// Goal: Reach Target from Start.
// Strategy: BFS from Start, ignoring self-loops.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        if (u != v) { // Ignore self-loops
            adj[u].push_back(v);
        }
    }

    int Start, Target;
    cin >> Start >> Target;

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

        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
