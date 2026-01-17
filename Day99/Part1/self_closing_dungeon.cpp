#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

// Problem 1: Dungeon With Self-Closing Paths
// Input: N, M, Start, Target, InitialHP.
// Edges: u, v, min_hp, max_hp, delta_hp.
// Rule: Edge passed -> disappears. 
// State: (u, hp).
// Pruning: If we reach (u, hp) again, we have FEWER edges than before.
// Being at same state with fewer options is never better.
// So simple visited[(u, hp)] is valid for "Existence".

struct Edge {
    int v;
    int min_hp, max_hp;
    int delta_hp;
};

int main() {
    int N, M, Start, Target, InitHP;
    if (!(cin >> N >> M >> Start >> Target >> InitHP)) return 0;
    
    vector<vector<Edge>> adj(N + 1);
    for(int i=0; i<M; ++i) {
        int u, v, min_h, max_h, d_h;
        cin >> u >> v >> min_h >> max_h >> d_h;
        adj[u].push_back({v, min_h, max_h, d_h});
    }
    
    // BFS State: u, hp
    queue<pair<int, int>> q;
    set<pair<int, int>> visited;
    
    q.push({Start, InitHP});
    visited.insert({Start, InitHP});
    
    while(!q.empty()) {
        auto [u, hp] = q.front(); q.pop();
        
        if (u == Target) {
            cout << "YES" << endl;
            return 0;
        }
        
        for(auto& e : adj[u]) {
            if (hp >= e.min_hp && hp <= e.max_hp) {
                int next_hp = hp + e.delta_hp;
                if (next_hp > 0) { // Assume HP must be > 0 to survive
                    if (!visited.count({e.v, next_hp})) {
                        visited.insert({e.v, next_hp});
                        q.push({e.v, next_hp});
                    }
                }
            }
        }
    }
    
    cout << "NO" << endl;
    return 0;
}
