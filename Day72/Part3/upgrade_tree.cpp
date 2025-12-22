#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DP state: dp[u] = max value from subtree u
// If we pick u, we get v[u] (and no descendants).
// If we don't pick u, we get sum(dp[child]).
// dp[u] = max(v[u], sum(dp[child]))

void dfs(int u, int p, const vector<vector<int>>& adj, const vector<int>& v, vector<long long>& dp) {
    long long sum_children = 0;
    for (int child : adj[u]) {
        if (child != p) {
            dfs(child, u, adj, v, dp);
            sum_children += dp[child];
        }
    }
    dp[u] = max((long long)v[u], sum_children);
}

int main() {
    int n;
    if (cin >> n) {
        if (n == 0) {
            cout << 0 << endl;
            return 0;
        }
        
        // Edges: n-1 lines
        vector<vector<int>> adj(n);
        for (int i = 0; i < n - 1; ++i) {
            int u, w;
            cin >> u >> w;
            // Assuming 0-indexed or 1-indexed? Usually 0-indexed in CP unless specified.
            // If input is 1-indexed, we adjust. Let's assume 0-indexed for now.
            // If values are large, check bounds.
            // Standard tree input.
            adj[u].push_back(w);
            adj[w].push_back(u);
        }

        vector<int> v(n);
        for (int i = 0; i < n; ++i) {
            cin >> v[i];
        }

        vector<long long> dp(n);
        // Root at 0
        dfs(0, -1, adj, v, dp);

        cout << dp[0] << endl;
    }
    return 0;
}
