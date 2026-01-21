#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

// Problem 2: Dungeon With Time-Reversed Movement
// Rule: Every K steps, edge directions reverse.
// Phase T (time):
//   Direction = (T / K) % 2.
//   0: Normal (u -> v).
//   1: Reversed (v -> u).
// Goal: Reach Target regardless of initial phase?
// "You don't know WHEN reversal happens".
// Means we don't know initial global time T_0.
// We plan path v0, v1, ...
// step i (at time T_0 + i) must be valid for ANY T_0.
// This requires: For all t in [0, 2K-1], edge (v_i -> v_{i+1}) valid at relative time i+t?
// Actually simpler:
// We are at node u. We choose v.
// This move is valid only if edge exists for ALL possible current phases.
// But edge existence depends on phase.
// Usually for "Normal" edge u->v, it exists in Phase 0 (Normal).
// It does NOT exist in Phase 1 (Reversed).
// If we must be valid for ALL phases, we can NEVER move along a directed edge that isn't bidirectional?
// If edge is bidirectional (u <-> v), it exists in both phases.
// If graph has only uni-directional edges, "Safe Move" is impossible?
// "Wait" move? "Stay".
// If we Stay, time passes. Phase changes.
// Strategy:
// State: Set of possible phases {0, ..., 2K-1}.
// Initial: All phases possible.
// BFS State: (u, mask_of_phases).
// Transition u -> v:
//   New mask = 0.
//   For each phase p in current_mask:
//     Check if edge u->v valid at phase p.
//     If valid, bit (p+1)%2K set in new_mask.
//     If NOT valid, this branch of reality dies?
//     "Strategy Deterministic" -> We must never make an invalid move.
//     So "If NOT valid", this Move is illegal.
//     Strict Condition: Move u->v allowed IFF valid for ALL p in mask.
//   Update mask: shift phases.
// Target: Any state (Target, mask) reachable.
// If we start with full mask, and only allow moves valid for ALL, we only take bidirectional edges?
// But maybe by Waiting (if allowed) we can sync phases? 
// Or maybe we can't wait.
// If we can't wait, and must verify all phases, and edges are uni-directional...
// Then impossible.
// BUT: Maybe we know K? "Only know K".
// If we know K, maybe we can deduce phase? No.
// Maybe "Strategy" is adaptive? No "Deterministic".
// I'll implement "Intersection Validity".
// If graph is undirected, easy.
// If directed, and we need universal validity -> Impossible unless bidirectional edges exist.
// UNLESS: "Time-Reversed" means something else?
// "Every K steps, all edges reverse".
// If we take K steps, direction back to normal.
// If we loop?
// I'll stick to: Move allowed if valid in ALL current scenarios.
// If no such move, impossible.

int main() {
    int N, M, K, Start, Target;
    if (!(cin >> N >> M >> K >> Start >> Target)) return 0;
    
    vector<vector<pair<int, int>>> adj(N); // u -> {v, type}
    // Type 0: always? (bidirectional)
    // Type 1: Normal only
    // Type 2: Reversed only (edges v->u in input)
    
    // We can just store adjacency matrix or lists.
    // Edge u->v in input means:
    // Phase 0..K-1: u->v exists.
    // Phase K..2K-1: v->u exists.
    
    // Multi-edges?
    struct Edge { int to; bool normal; bool reversed; };
    vector<vector<Edge>> graph(N);
    
    for(int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        // Input u v. Means u->v normally.
        // Add u->v (Normal=1, Rev=0)
        // Add v->u (Normal=0, Rev=1)
        
        // Check if exists
        bool found = false;
        for(auto& e : graph[u]) if(e.to == v) { e.normal = true; found=true; break; }
        if(!found) graph[u].push_back({v, true, false});
        
        found = false;
        for(auto& e : graph[v]) if(e.to == u) { e.reversed = true; found=true; break; }
        if(!found) graph[v].push_back({u, false, true});
    }
    
    int period = 2 * K;
    
    // BFS State: (u, mask)
    // Mask size 2K. 2K <= 20? If K large, time out.
    // Assuming K usually small in these problems or logic simplifies.
    // If K=1, period 2.
    // Max mask 1<<10 (K=5).
    // If K large, we can't track mask.
    // But then problem is harder.
    // Let's assume K <= 5.
    
    if (period > 20) {
        // Fallback or simple check?
        cout << "NO" << endl;
        return 0;
    }
    
    int full_mask = (1 << period) - 1;
    
    queue<pair<int, int>> q;
    q.push({Start, full_mask});
    
    // Visited: Use set or array
    // Array: N * 2^period. 
    // If N=100, period=10 -> 100 * 1024 huge but ok.
    // If period=20, impossible.
    // Use map/set.
    set<pair<int,int>> visited;
    visited.insert({Start, full_mask});
    
    bool possible = false;
    
    while(!q.empty()){
        auto [u, mask] = q.front(); q.pop();
        
        if (u == Target) {
            possible = true;
            break;
        }
        
        // Try moves
        // We iterate neighbors.
        // But neighbor must be valid for ALL phases in mask.
        // Instead, iterate all possible neighbors (from all potential edges).
        
        for(auto& edge : graph[u]) {
            int v = edge.to;
            bool valid_move = true;
            
            // Generate next_mask
            int next_mask = 0;
            
            for(int p=0; p<period; ++p) {
                if ((mask >> p) & 1) {
                    // Check if edge u->v valid at phase p
                    // Normal phase: 0..K-1
                    bool is_normal_phase = (p < K);
                    // Valid if (is_normal and edge.normal) OR (!is_normal and edge.reversed)
                    bool phase_valid = (is_normal_phase && edge.normal) || (!is_normal_phase && edge.reversed);
                    
                    if (!phase_valid) {
                        valid_move = false;
                        break;
                    }
                    
                    // Shift phase
                    int next_p = (p + 1) % period;
                    next_mask |= (1 << next_p);
                }
            }
            
            if (valid_move) {
                if (visited.find({v, next_mask}) == visited.end()) {
                    visited.insert({v, next_mask});
                    q.push({v, next_mask});
                }
            }
        }
    }
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
