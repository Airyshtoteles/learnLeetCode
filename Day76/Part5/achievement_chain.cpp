#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool solve() {
    int n, m;
    if (!(cin >> n >> m)) return false;
    
    vector<vector<int>> adj(n);
    vector<int> in_degree(n, 0);
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        if (u >= 0 && u < n && v >= 0 && v < n) {
            adj[u].push_back(v);
            in_degree[v]++;
        }
    }
    
    vector<int> bonus(n);
    for (int i = 0; i < n; ++i) {
        cin >> bonus[i];
    }
    
    queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0) {
            q.push(i);
        }
    }
    
    int count = 0;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        count++;
        
        // Process normal dependencies
        for (int v : adj[u]) {
            in_degree[v]--;
            if (in_degree[v] == 0) {
                q.push(v);
            }
        }
        
        // Process bonus
        int target = bonus[u];
        if (target >= 0 && target < n) {
            in_degree[target]--;
            if (in_degree[target] == 0) {
                q.push(target);
            }
        }
    }
    
    return count == n;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
