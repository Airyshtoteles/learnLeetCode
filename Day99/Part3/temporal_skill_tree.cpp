#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <set>

using namespace std;

// Problem 3: Skill Tree With Temporal Locks
// State: (Node, Time).
// BFS.
// Constraints: Time intervals.
// Inputs: N, T_target, StartTime, Edges (u, v, t_min, t_max, dt, cost).
// Cost (Energy) check. State: (Node, Time, Energy).
// Since Energy is resource, we want Min Energy for (Node, Time)?
// Or just reachability? "Energi terbatas" implies distinct limit or minimization.
// I'll assume standard MaxEnergy input and cost subtraction.

struct Edge {
    int v;
    int t_min, t_max, dt, cost;
};

int main() {
    int N, Target, StartTime, Energy;
    if (!(cin >> N >> Target >> StartTime >> Energy)) return 0;
    
    int M; cin >> M;
    vector<vector<Edge>> adj(N + 1);
    for(int i=0; i<M; ++i) {
        int u, v, tmin, tmax, dt, c;
        cin >> u >> v >> tmin >> tmax >> dt >> c;
        adj[u].push_back({v, tmin, tmax, dt, c});
    }
    
    // BFS State: u, time, energy
    // Visited optimization: Max energy at (u, time).
    // If we reach (u, time) with less energy, it's useless.
    // Time can range? Assume bounds? Or map?
    // Using map for sparse time.
    
    queue<tuple<int, int, int>> q;
    map<pair<int, int>, int> max_energy_at;
    
    q.push({1, StartTime, Energy}); // Assume Start Node 1
    max_energy_at[{1, StartTime}] = Energy;
    
    while(!q.empty()) {
        auto [u, t, e] = q.front(); q.pop();
        
        if (e < max_energy_at[{u, t}]) continue; // Outdated state
        
        if (u == Target) {
            cout << "YES" << endl;
            return 0;
        }
        
        for(const auto& edge : adj[u]) {
            if (t >= edge.t_min && t <= edge.t_max) {
                if (e >= edge.cost) {
                    int next_t = t + edge.dt;
                    int next_e = e - edge.cost;
                    
                    if (max_energy_at.find({edge.v, next_t}) == max_energy_at.end() || 
                        max_energy_at[{edge.v, next_t}] < next_e) {
                        
                        max_energy_at[{edge.v, next_t}] = next_e;
                        q.push({edge.v, next_t, next_e});
                    }
                }
            }
        }
    }
    
    cout << "NO" << endl;
    return 0;
}
