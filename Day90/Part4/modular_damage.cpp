#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

// Problem: Infinite Damage With Modular Forgetting
// Rule: Cannot repeat prefix sum modulo M.
// Start at 0. Path length <= M.
// Goal: Reach sum >= H.
// Maximize sum of simple path in graph: Nodes 0..M-1. Edges u -> (u+d)%M with weight d.
// Strategy: DFS with pruning.

long long H;
int M, N;
vector<long long> D;
vector<bool> visited;
bool possible = false;
long long max_D = 0;

void dfs(int u, long long current_sum, int depth) {
    if (possible) return;
    if (current_sum >= H) {
        possible = true;
        return;
    }
    
    // Pruning
    // Max possible remaining sum is (M - 1 - depth) * max_D??
    // Actually we can make at most M-1 steps total (visiting M nodes).
    // Remaining steps = (M - 1) - depth? 
    // Wait, if visited count is depth+1. Max total nodes M.
    // Max moves = M - 1.
    // If we are at 'u' (depth moves made), we can make at most (M - 1 - depth) more moves.
    // Actually, simply: We can visit unvisited nodes. Count = M - (depth + 1).
    // Pruning: current_sum + (remaining_nodes) * max_D < H -> Stop.
    
    int remaining = M - 1 - depth;
    if (remaining <= 0) return;
    if (current_sum + (long long)remaining * max_D < H) return;

    for (long long val : D) {
        int v = (u + val) % M;
        if (!visited[v]) {
            visited[v] = true;
            dfs(v, current_sum + val, depth + 1);
            visited[v] = false;
            if (possible) return;
        }
    }
}

int main() {
    if (!(cin >> H >> M >> N)) return 0;

    D.resize(N);
    for(int i=0; i<N; i++) {
        cin >> D[i];
        max_D = max(max_D, D[i]);
    }
    
    // Sort descending for greedy DFS
    sort(D.begin(), D.end(), greater<long long>());

    // Start at 0 (visited)
    // Actually, "Prefix sum modulo M". Initial is 0.
    // Move: current -> (current + d) % M.
    // Check if new mod is visited.
    
    visited.assign(M, false);
    visited[0] = true;
    
    if (H == 0) {
        cout << "YES" << endl;
        return 0;
    }

    dfs(0, 0, 0);

    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
