#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

struct State {
    int u;
    map<int, int> timers; // cooldown -> time_left
    
    bool operator<(const State& other) const {
        if (u != other.u) return u < other.u;
        return timers < other.timers;
    }
};

struct Edge {
    int v;
    int c;
};

bool solve() {
    int n, m;
    if (!(cin >> n >> m)) return false;
    
    vector<vector<Edge>> adj(n);
    set<int> all_cooldowns;
    for (int i = 0; i < m; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({v, c});
        adj[v].push_back({u, c});
        all_cooldowns.insert(c);
    }
    
    // BFS
    // State: u, map<cooldown, timer>
    // Since we only care about timers > 0, we remove 0s.
    // Optimization: If we reach u with a subset of timers (or smaller values), we are better.
    // But for simplicity, just use exact state matching.
    // If N is small, this might pass.
    // If C is large, timers can be large.
    // But we only care if timer > 0.
    // Max timer is max(C).
    // If C is huge, we can't simulate step by step?
    // Wait, "selama c langkah berikutnya".
    // This means for the next c moves, we cannot use edge with cooldown c.
    // So we decrement all timers by 1 at each step.
    
    queue<State> q;
    set<State> visited;
    
    State startState;
    startState.u = 0;
    q.push(startState);
    visited.insert(startState);
    
    while (!q.empty()) {
        State curr = q.front();
        q.pop();
        
        if (curr.u == n - 1) return true;
        
        // Prepare next timers: decrement all by 1, remove if <= 0
        map<int, int> next_timers_base;
        for (auto const& [cd, time] : curr.timers) {
            if (time > 1) {
                next_timers_base[cd] = time - 1;
            }
        }
        
        for (auto& edge : adj[curr.u]) {
            // Check if edge.c is blocked
            if (curr.timers.count(edge.c) && curr.timers.at(edge.c) > 0) {
                continue;
            }
            
            // Use edge
            State nextState;
            nextState.u = edge.v;
            nextState.timers = next_timers_base;
            
            // Add new block
            // "tidak boleh melewati edge lain dengan cooldown yang sama selama c langkah berikutnya"
            // So we set timer for edge.c to edge.c
            // If edge.c > 0, we block it.
            if (edge.c > 0) {
                // If it was already blocked (shouldn't be, we checked), update?
                // Or take max?
                // Logic: We just used it. Now it's blocked for c steps.
                // If it was blocked for 5 steps, and we used it (impossible), ...
                // So we just set it.
                // Note: next_timers_base already decremented old timers.
                // If edge.c was in next_timers_base, it means it was > 1 before.
                // But we checked curr.timers[edge.c] == 0 (or not present).
                // So it won't be in next_timers_base.
                nextState.timers[edge.c] = edge.c;
            }
            
            if (visited.find(nextState) == visited.end()) {
                visited.insert(nextState);
                q.push(nextState);
            }
        }
    }
    
    return false;
}

int main() {
    cout << (solve() ? "true" : "false") << endl;
    return 0;
}
