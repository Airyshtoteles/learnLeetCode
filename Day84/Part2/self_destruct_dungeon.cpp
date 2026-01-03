#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem: Find a path from Start to Target such that no node is visited more than once.
// This is the definition of a Simple Path.
// In a general graph, finding *any* simple path is easy (BFS/DFS).
// The constraint "Node visited > 1 time will be destroyed" implies we cannot use a node twice.
// So we just need to find if S and T are connected.
// Standard BFS finds the shortest path, which is by definition simple (no cycles).
// So we just run BFS.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> adj(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Assuming undirected, or directed? "Dungeon berupa graph". Usually undirected unless specified.
        // Let's assume undirected for dungeon.
    }

    int Start, Target;
    cin >> Start >> Target;

    if (Start == Target) {
        cout << "Possible" << endl;
        return 0;
    }

    queue<int> q;
    q.push(Start);
    vector<bool> visited(N, false);
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
