#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 3: Skill DAG With Limited Reuse
// Skill graph is DAG.
// Parent -> Child. "Taking skill unlocks child".
// To take child, we must have "unlocked" it.
// Interpretation: Unlocking means having a path from a root?
// Usually: Taking P unlocks C. Just like standard tree.
// To take T, we need one Parent P. T must be connected to Start.
// Since we want minimal cost/usage to reach T.
// This is simply Shortest Path in DAG from any Root to T.
// Max usage K.
// If ShortestPath(Root -> T) has length <= K, YES.

int main() {
    int N, M, K, T;
    if (!(cin >> N >> M >> K >> T)) return 0;
    
    vector<vector<int>> adj(N + 1);
    vector<int> in_degree(N + 1, 0);
    
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // Roots are nodes with in_degree 0? No, usually "Starter skills" are explicitly given or roots.
    // Assuming any node with in_degree 0 is a starter skill.
    // Or we can start at any node? "Taking skill unlocks child".
    // Usually means you can take a root skill freely.
    
    // BFS from all roots to find min distance to T.
    // Usage count = number of skills taken.
    // In a path u -> v -> ... -> T, we take count(nodes) skills.
    
    queue<pair<int, int>> q;
    vector<int> min_dist(N + 1, 1e9);
    
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            q.push({i, 1}); // Taking root is 1 skill
            min_dist[i] = 1;
        }
    }
    
    while (!q.empty()) {
        auto [u, dist] = q.front();
        q.pop();
        
        if (u == T) {
            // Found T.
            if (dist <= K) {
                cout << "YES" << endl;
                return 0;
            }
        }
        
        if (dist >= K) continue; // Cannot extend further
        
        for (int v : adj[u]) {
            if (min_dist[v] > dist + 1) {
                min_dist[v] = dist + 1;
                q.push({v, dist + 1});
            }
        }
    }
    
    cout << "NO" << endl;
    
    return 0;
}
