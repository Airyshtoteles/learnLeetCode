#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <map>

using namespace std;

// Problem 1: Quantum Respawn Paradox
// State: (Mask, CurrentNode).
// Actions:
// 1. Move U->V (if edge exists). Cost 0.
// 2. Die. Respawn at C (if C in Mask). Cost: Remove other C' (Player chooses).
//    New State: (Mask \ {C'}, C).
// Goal: Reach BossNode.
// Constraint: KeyCheckpoint must be in Mask.
//
// Logic:
// Use BFS/Dijkstra on States.
// Maximize Mask size? Or just reachability.
// If we can reach Boss with KeyCheckpoint in Mask, return YES.

int N, M_edges, Start, Boss, KeyCheckpoint;
vector<vector<int>> adj;
vector<int> checkpoints; // List of node IDs that are checkpoints

map<pair<int, int>, bool> visited; // (Mask, u)

int get_initial_mask() {
    int mask = 0;
    for(int i=0; i<checkpoints.size(); ++i) mask |= (1 << i);
    return mask;
}

int get_checkpoint_idx(int u) {
    for(int i=0; i<checkpoints.size(); ++i) {
        if(checkpoints[i] == u) return i;
    }
    return -1;
}

int main() {
    if (!(cin >> N >> M_edges >> Start >> Boss >> KeyCheckpoint)) return 0;
    
    adj.resize(N + 1);
    for(int i=0; i<M_edges; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v); // Directed
    }
    
    int K; cin >> K;
    checkpoints.resize(K);
    for(int i=0; i<K; ++i) cin >> checkpoints[i];
    
    // KeyCheckpoint must be in checkpoints list. Find its index.
    int key_idx = get_checkpoint_idx(KeyCheckpoint);
    if (key_idx == -1) {
        // Boss requires KeyCheckpoint, but it's not a checkpoint?
        // Or KeyCheckpoint IS a checkpoint ID.
        cout << "NO" << endl;
        return 0;
    }

    queue<pair<int, int>> q;
    int init_mask = get_initial_mask();
    q.push({init_mask, Start});
    visited[{init_mask, Start}] = true;
    
    while(!q.empty()) {
        auto [mask, u] = q.front(); q.pop();
        
        // Check Required
        bool key_present = (mask >> key_idx) & 1;
        if (!key_present) continue; // Invalid path
        
        if (u == Boss) {
            cout << "YES" << endl;
            return 0;
        }
        
        // 1. Walk
        for(int v : adj[u]) {
            if (!visited.count({mask, v})) {
                visited[{mask, v}] = true;
                q.push({mask, v});
            }
        }
        
        // 2. Die & Respawn (Teleport)
        // Can respawn at any C in mask.
        // Cost: Remove a C' in mask (C' != C).
        // Iterate over Targets (To Respawn)
        for(int i=0; i<checkpoints.size(); ++i) {
            if ((mask >> i) & 1) { // Checkpoint i is available
                int target_node = checkpoints[i];
                
                // Iterate over Sacrifices
                // Can sacrifice any j != i in mask
                // Only need to show ONE valid sacrifice allows transition.
                // Actually, sacrifice REDUCES options.
                // We want to KEEP options.
                // Is there a case where sacrificing C1 moves us to C2, and SACRIFICING C1 is better than C3?
                // No. All removals are bad.
                // We want to remove the LEAST useful checkpoint.
                // But this is BFS. We explore all options.
                
                for(int j=0; j<checkpoints.size(); ++j) {
                    if (i == j) continue;
                    if ((mask >> j) & 1) {
                        int next_mask = mask & ~(1 << j); // Remove j
                        
                        // We are now at target_node
                        // Check Key requirement early
                        if ((next_mask >> key_idx) & 1) {
                            if (!visited.count({next_mask, target_node})) {
                                visited[{next_mask, target_node}] = true;
                                q.push({next_mask, target_node});
                            }
                        }
                    }
                }
            }
        }
    }
    
    cout << "NO" << endl;
    return 0;
}
