#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

// Problem 6: Economy With Transaction Cooldown Graph
// State: (Node, CooldownsVector, Money).
// CooldownsVector: vector of size N.
// Constraints: N is small? "Day 96 biasa". N <= 10 or 15?
// If N is large, state space explodes.
// Given "Graph" and "Cooldown", maybe N is small.
// Let's assume N <= 15.
// State: Cooldowns[N].
// 
// Dijkstra.
// Maximize Money? Or Reach Target?
// "Money tidak boleh negatif". "Target W".
// BFS/Dijkstra to find IF we can reach W.
// State: (CurrentNode, Cooldowns) -> Max Money.
// 
// Cooldown Logic:
// Neighbors get cooldown `c`.
// Wait, `c` steps.
// This means we have to decrement cooldowns steps by step.
// 
// State Representation:
// `vector<int> current_cooldowns`
// Map< pair<int, vector<int>>, int > visited_money.
// 
// Transitions:
// From `u`, Cooldowns `cd`.
// Try all neighbors `v`.
// Cost/Gain `g`.
// If `cd[v] == 0`:
//    New Money `M' = M + g`.
//    If `M' < 0` invalid.
//    New Cooldowns `cd'`:
//       for all i: cd'[i] = max(0, cd[i] - 1)
//       for neighbor n of v (and v itself?): cd'[n] = max(cd'[n], c).
//       Wait, "setelah memakai transaksi i, transaksi tetangganya cooldown c langkah".
//       Does `i` itself cooldown? Usually yes (neighbor of itself or explicit).
//       Let's assume `v` and `neighbors(v)` get `c` cooldown.
//    Push priority queue.

struct State {
    int u;
    vector<int> cds;
    int money;
    
    // For Priority Queue? We want to MAXIMIZE money.
    // So less than operator should put SMALLER money at top? No, MAX heap.
    bool operator<(const State& other) const {
        return money < other.money;
    }
};

int main() {
    int N, M_edges, TargetW, StartNode, CoolSteps;
    int CurrentW;
    
    if (!(cin >> N >> M_edges >> CurrentW >> TargetW >> StartNode >> CoolSteps)) return 0;
    
    vector<int> Gain(N);
    for(int i=0; i<N; ++i) cin >> Gain[i];
    
    vector<vector<int>> adj(N);
    for(int i=0; i<M_edges; ++i) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        // adj[v].push_back(u); // Directed or Undirected? "Transaksi tetangga". Undirected graph usually? Or Transaction flow? Assume Directed.
    }
    
    // Map to track max money for (u, cds)
    map<pair<int, vector<int>>, int> best_money;
    
    priority_queue<State> pq;
    vector<int> init_cds(N, 0);
    
    // Initial state
    // Do we process StartNode immediately?
    // Usually start state is "At StartNode". We act *from* there.
    pq.push({StartNode, init_cds, CurrentW});
    best_money[{StartNode, init_cds}] = CurrentW;
    
    while(!pq.empty()) {
        auto [u, cds, money] = pq.top();
        pq.pop();
        
        if (money >= TargetW) {
            cout << "YES" << endl;
            return 0;
        }
        
        if (best_money.count({u, cds}) && best_money[{u, cds}] > money) continue;
        
        // Try to move to neighbor v (Execute transaction v?)
        // Interpret: Nodes are transactions?
        // "Transaksi adalah node graph".
        // "Setelah memakai transaksi i, ..."
        // So moving to `v` means executing `v`.
        
        for(int v : adj[u]) {
            if (cds[v] == 0) {
                int next_money = money + Gain[v];
                if (next_money < 0) continue;
                
                // Update Cooldowns
                vector<int> next_cds = cds;
                // Decay
                for(int& x : next_cds) x = max(0, x - 1);
                
                // Apply Effect of v
                // Tetangga v (neighbors of v) get cooldown `CoolSteps`.
                // Does `v` get cooldown? Usually yes.
                // Does `u` (previous) get cooldown? No, neighbors of `v`.
                // Note: v is neighbor of u. So u gets cooldown? if undirected.
                // Assuming "neighbors of the executed node get locked".
                
                // We need neighbors of `v`.
                next_cds[v] = max(next_cds[v], CoolSteps);
                for(int neighbor : adj[v]) {
                    next_cds[neighbor] = max(next_cds[neighbor], CoolSteps);
                }
                
                if (!best_money.count({v, next_cds}) || best_money[{v, next_cds}] < next_money) {
                    best_money[{v, next_cds}] = next_money;
                    pq.push({v, next_cds, next_money});
                }
            }
        }
        // Also allow "Wait"?
        // If we wait, cooldowns decay.
        // next_money = money.
        // next_cds = decay(cds).
        // Stay at u?
        // If we allow waiting, we can recover cooldowns.
        vector<int> wait_cds = cds;
        bool changed = false;
        for(int& x : wait_cds) {
            if (x > 0) {
                x--;
                changed = true;
            }
        }
        
        if (changed) {
             if (!best_money.count({u, wait_cds}) || best_money[{u, wait_cds}] < money) {
                best_money[{u, wait_cds}] = money;
                pq.push({u, wait_cds, money});
            }
        }
    }
    
    cout << "NO" << endl;
    return 0;
}
