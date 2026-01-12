#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 5: Multi-Agent Dungeon With Shared Cooldown
// K agents. Global cooldown C.
// Only one agent moves per turn.
// Move, Wait C steps, Move...
// This means effective speed is 1 move per (C+1) time text.
// If winning condition is "Any agent reaches target".
// Since agents are independent (unless blocking each other?), and they navigate Graph.
// We can just calculate shortest path for EACH agent to target.
// Minimum moves M_i.
// Total Time T_i = M_i * (1 + C) - C (last wait not needed if reached? Or is it?).
// "Shared cooldown global C".
// Usually, "Cooldown" means you must wait before NEXT move.
// If Agent 1 moves at t=0. Next move allowed t=C+1.
// If reaching target is the goal, the last move lands on target.
// Time taken = (Moves - 1) * (C + 1) + 1. (Assuming 1 tick for move).
// Or just "Turns".
// If "Can strategy surely exist?" -> Just check reachability.
// If any agent can reach, YES.
// Unless "One agent dies" is triggered by something.
// Assuming "Dies" is standard danger not detailed here, or maybe implies we have backup.
// The core question is Reachability.
// Inti: "Turn-based reachability".
// So simply: Run BFS for each agent. If min_dist < Infinity, YES.
// Output the min time? Or just YES/NO? "Apakah strategi pasti ada?" -> YES/NO.
// I will output YES/NO.

int main() {
    int K, C_cooldown, N, M;
    if (!(cin >> K >> C_cooldown >> N >> M)) return 0;
    
    int Target;
    cin >> Target;
    
    vector<int> starts(K);
    for (int i = 0; i < K; ++i) cin >> starts[i];
    
    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Assuming Undirected Dungeon unless specified
    }
    
    // Check reachability for any agent
    bool possible = false;
    
    for (int k = 0; k < K; ++k) {
        // BFS
        queue<int> q;
        q.push(starts[k]);
        vector<bool> visited(N + 1, false);
        visited[starts[k]] = true;
        
        bool reached = false;
        if (starts[k] == Target) reached = true;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (u == Target) {
                reached = true;
                break;
            }
            
            for (int v : adj[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }
        
        if (reached) {
            possible = true;
            break;
        }
    }
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
