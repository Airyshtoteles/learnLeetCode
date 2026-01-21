#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <queue>
#include <iomanip>

using namespace std;

// Problem 6: Economy With Turing-Complete Contracts
// (Interpreted as: Currency Exchange with Arbitrage Detection)
// Maximize wealth at target node N, given start node 1 with 1.0 unit.
// Edges u -> v with rate w.
// Use Bellman-Ford with Logarithms to find longest path and detect positive cycles.

struct Edge {
    int u, v;
    double rate;
};

const double INF = 1e18; // Logic infinity for distances

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<Edge> edges;
    vector<vector<int>> adj(N + 1); // For reachability check
    
    for (int i = 0; i < M; ++i) {
        int u, v;
        double w;
        cin >> u >> v >> w;
        edges.push_back({u, v, w});
        adj[u].push_back(v);
    }
    
    // Bellman-Ford
    // Use log probabilities.
    // rate R -> log(R).
    // Multiply rates -> Add logs.
    // Maximize sum of logs.
    // Init dists to -INF.
    
    vector<double> dist(N + 1, -INF);
    dist[1] = 0.0; // log(1) = 0
    
    // Run N-1 iterations
    for (int i = 0; i < N - 1; ++i) {
        bool updated = false;
        for (const auto& e : edges) {
            if (dist[e.u] > -INF * 0.5) { // If reachable
                double new_dist = dist[e.u] + log(e.rate);
                if (new_dist > dist[e.v] + 1e-9) {
                    dist[e.v] = new_dist;
                    updated = true;
                }
            }
        }
        if (!updated) break;
    }
    
    // Check for positive cycles (which appear as relaxable edges after N-1 steps)
    // And check if such a cycle can reach Node N.
    
    vector<bool> in_cycle_flow(N + 1, false);
    queue<int> q;
    
    for (const auto& e : edges) {
        if (dist[e.u] > -INF * 0.5) {
             double new_dist = dist[e.u] + log(e.rate);
             if (new_dist > dist[e.v] + 1e-9) {
                 // e.v is updated, so it is part of or reachable from a positive cycle
                 // We need to see if this propagates to N
                 if (!in_cycle_flow[e.v]) {
                     in_cycle_flow[e.v] = true;
                     q.push(e.v);
                 }
                 // Logic: Just pushing e.v to a queue and doing BFS to see what it hits.
             }
        }
    }
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        
        for(int v : adj[u]){
            if(!in_cycle_flow[v]){
                in_cycle_flow[v] = true;
                q.push(v);
            }
        }
    }
    
    if (in_cycle_flow[N]) {
        cout << "INFINITY" << endl;
    } else {
        if (dist[N] <= -INF * 0.5) {
            cout << "0.00000" << endl; // Unreachable
        } else {
            cout << fixed << setprecision(5) << exp(dist[N]) << endl;
        }
    }

    return 0;
}
