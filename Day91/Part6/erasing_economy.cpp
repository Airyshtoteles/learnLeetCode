#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

// Problem 6: Economy With Self-Erasing History
// Rules: History stored modulo K.
// Condition: If current history (x % K) matches any PREVIOUS history in the current run -> Reset.
// Goal: Reach X >= W without triggering reset.
// Equivalently: Find a simple path in the graph where nodes are residues [0..K-1].
// State space: (Current Value).
// But constraint is on residues.
// Max Path Length <= K.
// BFS State: (CurrentValue).
// Pruning: If we reach residue `r` with Value `v`, and we previously reached `r` with `v' >= v` ?
// Usually larger value is better? Assumed Economy grows.
// Ops: assume +1, *2 like Day 90. Or generalized?
// Prompt says "Ekonomi state (x)". "Target x >= W".
// I'll assume standard ops {+1, *2}.
// State check: Avoid repeating `val % K` in the path.
// This means path length <= K residues.
// BFS: Queue stores (CurrentValue, MaskOfVisitedResidues).
// If K is small (<= 20).
// If residue repeat -> Invalid path.
// If K is large (e.g., 10^5), collision is structural. K is "modulus".
// If K is large, maybe we just do standard BFS on values?
// Path residues must be distinct.
// If K is large enough, collisions are avoidable.
// If K is small, collisions restrict us.
// Since "Finite-memory", likely K is constraint.
// I will implement BFS with `set<int> path_residues`.
// Wait, for large state space, `set` is heavy.
// But max depth is K. If K is big, maybe we hit W quickly?
// If K=10^9, distinct check is trivial.
// If K=5, strict constraint.
// I'll use `bitset` or `vector<bool>` if K is small.
// Or just `set` for generality since K likely <= W or small.

struct State {
    long long val;
    long long visited_mask; // For K <= 60
};

// If K > 60, use set?
// Let's assume K <= 20 for mask, or use set for path.
// Actually, simple DFS might be better for finding "Simple Path in Residue Graph".
// DFS(val, path_mask).
// If val >= W, return True.

long long W;
long long K;
bool possible = false;

void dfs(long long val, vector<bool>& visited_mod) {
    if (possible) return;
    if (val >= W) {
        possible = true;
        return;
    }
    
    // Heuristic: If val is large relative to W, valid?
    // Ops: +1, *2.
    
    // Try +1
    long long next_val = val + 1;
    long long mod = next_val % K;
    if (!visited_mod[mod]) {
        visited_mod[mod] = true;
        dfs(next_val, visited_mod);
        visited_mod[mod] = false;
        if(possible) return;
    }
    
    // Try *2
    next_val = val * 2;
    mod = next_val % K;
    if (!visited_mod[mod]) {
        visited_mod[mod] = true;
        dfs(next_val, visited_mod);
        visited_mod[mod] = false;
        if(possible) return;
    }
}

int main() {
    // Input: Start W K
    long long Start;
    if (!(cin >> Start >> W >> K)) return 0;
    
    // Check initial
    if (Start >= W) {
        cout << "YES" << endl;
        return 0;
    }
    
    vector<bool> visited_mod(K, false);
    visited_mod[Start % K] = true;
    
    dfs(Start, visited_mod);
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
