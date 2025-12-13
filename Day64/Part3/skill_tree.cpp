#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// dp[u][k] = min cost to pick k nodes in subtree u
// We want to maximize k such that cost <= M.
// Since we want max nodes, we can use min cost for k nodes.
// Max nodes in subtree u is sz[u].
// dp[u] will be a vector of size sz[u] + 1.

int N, M;
vector<int> cost;
vector<vector<int>> adj;
vector<int> sz;
vector<vector<int>> dp;

void dfs(int u) {
    sz[u] = 1;
    dp[u] = {0, cost[u]}; // 0 nodes: cost 0. 1 node (u itself): cost[u].
    // Wait, if we pick u, we must pick u.
    // If we don't pick u, we can't pick any children.
    // So dp[u][0] = 0 (pick nothing).
    // dp[u][1] = cost[u] (pick u).
    // Then we merge children.
    // If we pick u, we can pick from children.
    // If we don't pick u, we pick 0 from children.
    
    // Actually, standard tree knapsack:
    // dp[u][k] = min cost to pick k nodes in subtree u, GIVEN that u is picked.
    // If u is not picked, count is 0, cost is 0.
    // So we only compute for case where u is picked.
    // At the end, we check if we can pick u or not.
    // But since we have a dummy root -1 (cost 0), we always pick -1.
    
    for (int v : adj[u]) {
        dfs(v);
        // Merge v into u
        int new_sz = sz[u] + sz[v];
        vector<int> new_dp(new_sz + 1, 1e9 + 7);
        
        // Knapsack merge
        // We are picking `i` nodes from current `u` (which includes u itself and some children processed so far)
        // and `j` nodes from child `v`.
        // Total `i+j` nodes.
        // Since we assume u is picked, we iterate i from 1 to sz[u].
        // j from 0 to sz[v].
        
        for (int i = 1; i <= sz[u]; ++i) {
            for (int j = 0; j <= sz[v]; ++j) {
                if (dp[u][i] + dp[v][j] <= M) { // Optimization
                    new_dp[i+j] = min(new_dp[i+j], dp[u][i] + dp[v][j]);
                }
            }
        }
        
        sz[u] = new_sz;
        dp[u] = new_dp;
    }
}

int main() {
    int num_edges;
    if (!(cin >> N >> num_edges)) return 0;
    
    cost.resize(N);
    for (int i = 0; i < N; ++i) cin >> cost[i];
    
    cin >> M;
    
    adj.resize(N + 1); // +1 for dummy root
    vector<int> in_degree(N, 0);
    
    for (int i = 0; i < num_edges; ++i) {
        int u, v;
        cin >> u >> v;
        // u unlocks v -> u is parent of v
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // Add dummy root N connecting to all nodes with in-degree 0
    cost.push_back(0); // Cost of dummy root is 0
    for (int i = 0; i < N; ++i) {
        if (in_degree[i] == 0) {
            adj[N].push_back(i);
        }
    }
    
    sz.resize(N + 1);
    dp.resize(N + 1);
    
    dfs(N);
    
    // Find max k such that dp[N][k] <= M
    int ans = 0;
    for (int k = 0; k <= sz[N]; ++k) {
        if (dp[N][k] <= M) {
            ans = k;
        }
    }
    
    // Subtract 1 because dummy root doesn't count as a skill
    // But wait, dummy root has cost 0.
    // If we pick k nodes including dummy root, we picked k-1 actual skills.
    // Is it possible to pick 0 nodes? Yes, cost 0.
    // If ans is 0, it means we picked nothing (not even dummy?).
    // But dummy is always picked in our DP state definition (dp[u] assumes u picked).
    // So ans will be at least 1 (dummy root).
    // Real answer is ans - 1.
    
    cout << max(0, ans - 1) << endl;
    
    return 0;
}
