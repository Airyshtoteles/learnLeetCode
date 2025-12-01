#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

map<vector<int>, bool> memo;
vector<vector<int>> affected;
int N;

bool can_win(vector<int>& state) {
    if (memo.count(state)) return memo[state];
    
    // Try all moves
    for (int i = 0; i < N; ++i) {
        // Find max k
        int max_k = state[i];
        for (int neighbor : affected[i]) {
            if (neighbor != i) {
                max_k = min(max_k, state[neighbor]);
            }
        }
        
        if (max_k == 0) continue;
        
        for (int k = 1; k <= max_k; ++k) {
            vector<int> next_state = state;
            for (int idx : affected[i]) {
                next_state[idx] -= k;
            }
            
            if (!can_win(next_state)) {
                return memo[state] = true;
            }
        }
    }
    
    return memo[state] = false;
}

bool solve_quantum_nim(vector<int> stones, vector<pair<int, int>> edges) {
    N = stones.size();
    affected.assign(N, vector<int>());
    
    // Build adjacency
    vector<vector<int>> adj(N);
    for (auto& edge : edges) {
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
    
    for (int i = 0; i < N; ++i) {
        affected[i].push_back(i);
        for (int neighbor : adj[i]) {
            affected[i].push_back(neighbor);
        }
    }
    
    memo.clear();
    return can_win(stones);
}

int main() {
    // Example 1
    vector<int> stones1 = {3, 3, 3};
    vector<pair<int, int>> edges1 = {{0, 1}, {1, 2}};
    
    cout << "Stones: {3, 3, 3}, Edges: {{0, 1}, {1, 2}}" << endl;
    if (solve_quantum_nim(stones1, edges1)) {
        cout << "Result: First Player Wins" << endl;
    } else {
        cout << "Result: Second Player Wins" << endl;
    }
    
    // Example 2
    vector<int> stones2 = {2, 2};
    vector<pair<int, int>> edges2 = {};
    
    cout << "Stones: {2, 2}, Edges: {}" << endl;
    if (solve_quantum_nim(stones2, edges2)) {
        cout << "Result: First Player Wins" << endl;
    } else {
        cout << "Result: Second Player Wins" << endl;
    }
    
    return 0;
}
