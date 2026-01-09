#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem: Skill Graph With Mutual Annihilation
// Condition: Taking two incomparable skills destroys them.
// Implication: The set of all skills required (Ancestors of T + T) must form a Chain.
// Algorithm:
// 1. Identify all ancestors of T (Set S).
// 2. Consider the subgraph induced by S.
// 3. Check if S forms a chain i.e., Total Order.
//    Using Kahn's Algorithm on Subgraph: At any step, the queue of available nodes must have size 1.

int main() {
    int N, M, T;
    if (!(cin >> N >> M >> T)) return 0;

    // Use 0-based indexing if input is 0-based, assuming 0-based for now.
    // If indices are likely 1-relative? Usually CP is 1-based, but N, M usually implies 0..N-1 or 1..N.
    // Let's assume standard integer IDs. If max ID >= N, resize.
    // We'll use adjacency lists.
    
    // Read edges
    vector<pair<int, int>> edges;
    vector<vector<int>> rev_adj(N);
    vector<vector<int>> adj(N);
    
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
        edges.push_back({u, v});
    }

    // 1. Find ancestors of T
    // BFS on rev_adj starting from T
    vector<bool> is_ancestor(N, false);
    queue<int> q;
    q.push(T);
    is_ancestor[T] = true;
    int ancestor_count = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ancestor_count++;

        for (int v : rev_adj[u]) {
            if (!is_ancestor[v]) {
                is_ancestor[v] = true;
                q.push(v);
            }
        }
    }

    // 2. Build Induced Graph (implicitly via degrees)
    // We only care about nodes in is_ancestor.
    // Compute in-degrees for subgraph.
    vector<int> in_degree(N, 0);
    for (auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        if (is_ancestor[u] && is_ancestor[v]) {
            in_degree[v]++;
        }
    }

    // 3. Topological Sort Check
    queue<int> topo_q;
    for (int i = 0; i < N; ++i) {
        if (is_ancestor[i]) {
            if (in_degree[i] == 0) {
                topo_q.push(i);
            }
        }
    }

    int processed = 0;
    bool valid = true;

    while (!topo_q.empty()) {
        if (topo_q.size() > 1) {
            valid = false;
            break;
        }

        int u = topo_q.front();
        topo_q.pop();
        processed++;

        for (int v : adj[u]) {
            if (is_ancestor[v]) {
                in_degree[v]--;
                if (in_degree[v] == 0) {
                    topo_q.push(v);
                }
            }
        }
    }

    if (valid && processed == ancestor_count) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }

    return 0;
}
