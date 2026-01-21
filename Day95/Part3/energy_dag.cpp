#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

// Problem 3: Skill DAG With Energy Regeneration
// Start Energy: Emax (Assumed standard unless input specifies).
// Cost C[i] to learn skill i.
// Effect: Energy -= C[i]. Then +1 Regen. Min(Emax).
// Check feasibility of reaching T.
// State: Max Energy at Node u.
// Why Max? Because more energy allows taking expensive children.
// Nodes with in-degree 0 are roots. Start there.
// If multiple parents lead to u?
// DAG structure: Taking u requires ???
// Usually "Prerequisite" implies logic.
// Simpler interpretation: Standard Graph Traversal.
// To reach u, we come from SOME parent p.
// If so, we essentially find a path from *some root* to T.
// Valid move p -> u: `energy_at_p >= Cost[u]`.
// `energy_at_u = min(Emax, energy_at_p - Cost[u] + 1)`.
// We want to maximize `energy_at_u`.
// Dijkstra (Max-Heap) or Topo Sort DP works since it's a DAG.
// Or simple BFS if weights not tricky. But here state value (Energy) is dynamic.
// Since we want MAX energy, and it's a DAG, we can just process in topological order?
// Or just iterate: Relax edges.
// `max_energy[u]` initialized to -1.
// Roots init to Emax.

int main() {
    int N, M, Emax, T;
    if (!(cin >> N >> M >> Emax >> T)) return 0;
    
    vector<int> cost(N + 1);
    for(int i=1; i<=N; ++i) cin >> cost[i];
    
    vector<vector<int>> adj(N + 1);
    vector<int> in_degree(N + 1, 0); // Not needed for general graph search unless strict DAG
    
    for(int i=0; i<M; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // BFS/Dijkstra logic
    // Maximize energy at each node.
    vector<int> max_e(N + 1, -1);
    priority_queue<pair<int, int>> pq;
    
    // Start nodes: Assuming In-Degree 0 nodes are starts.
    // Or scan all? "Start skill" not defined. Assume roots.
    // Cost of Root? "Mengambil skill butuh energi". 
    // Usually Root is free or costs if we "take" it.
    // If we assume we START with Emax BEFORE taking the root?
    // Cost applies to taking a node.
    // So if Root cost > Emax, can't take.
    // If can take, Energy = min(Emax, Emax - Cost + 1).
    
    for(int i=1; i<=N; ++i){
        if(in_degree[i] == 0) {
            if (Emax >= cost[i]) {
                int next_e = min(Emax, Emax - cost[i] + 1);
                if (next_e > max_e[i]) {
                    max_e[i] = next_e;
                    pq.push({next_e, i});
                }
            }
        }
    }
    
    while(!pq.empty()){
        auto [e, u] = pq.top();
        pq.pop();
        
        if (e < max_e[u]) continue;
        
        if (u == T) {
            cout << "YES" << endl;
            return 0;
        }
        
        for (int v : adj[u]) {
            // Try to move to v
            // Need e >= cost[v]
            if (e >= cost[v]) {
                int next_e = min(Emax, e - cost[v] + 1);
                if (next_e > max_e[v]) {
                    max_e[v] = next_e;
                    pq.push({next_e, v});
                }
            }
        }
    }
    
    cout << "NO" << endl;
    
    return 0;
}
