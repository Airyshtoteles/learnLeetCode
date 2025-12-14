#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Function to calculate GCD
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Max Clique Solver
int max_clique(const vector<vector<int>>& adj, int n) {
    // Simple recursive max clique with pruning
    // This is exponential but fast for small N or sparse graphs
    // For N <= 50, it should pass if not worst case
    
    int max_size = 0;
    
    auto recurse = [&](auto&& self, vector<int>& candidates, vector<int>& current) -> void {
        if (current.size() + candidates.size() <= max_size) return;
        
        if (candidates.empty()) {
            max_size = max(max_size, (int)current.size());
            return;
        }
        
        while (!candidates.empty()) {
            int v = candidates.back();
            candidates.pop_back();
            
            // Try adding v
            vector<int> next_candidates;
            for (int u : candidates) {
                // Check if u is connected to v
                bool connected = false;
                for (int neighbor : adj[v]) {
                    if (neighbor == u) {
                        connected = true;
                        break;
                    }
                }
                if (connected) {
                    next_candidates.push_back(u);
                }
            }
            
            current.push_back(v);
            self(self, next_candidates, current);
            current.pop_back();
        }
    };
    
    vector<int> candidates(n);
    iota(candidates.begin(), candidates.end(), 0);
    vector<int> current;
    
    recurse(recurse, candidates, current);
    
    return max_size;
}

int main() {
    int n;
    if (!(cin >> n)) return 0;

    vector<int> cooldown(n);
    for (int i = 0; i < n; ++i) cin >> cooldown[i];

    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }

    // Build graph
    // Edge (i, j) if gcd(cooldown[i], cooldown[j]) == 1
    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (gcd(cooldown[i], cooldown[j]) == 1) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    cout << max_clique(adj, n) << endl;

    return 0;
}
