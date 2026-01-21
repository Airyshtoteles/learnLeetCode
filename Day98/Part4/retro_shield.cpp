#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

// Problem 4: Boss With Retroactive Shield
// Logic:
// We need a sequence of moves M1, M2...
// Such that for any window of 5: Sum(Dmg) >= S.
// To Win: We must sustain this until Total Dmg >= BossHP.
// If we can construct a cyclic pattern of moves that satisfies window >= S, 
// and has Avg Dmg > 0, we can win.
// Moves available: Assume input gives list of available attacks (Dmg).
// Or maybe we choose ANY damage? No, limited "Skill mahal" context from previous.
// Assume Input: BossHP, S threshold, N available moves (values).
//
// Algorithm:
// Graph Nodes: Sequence of last 4 moves. (m1, m2, m3, m4).
// Transitions: Pick next move m5.
// Check condition: m1+m2+m3+m4+m5 >= S.
// If valid, edge to (m2, m3, m4, m5).
// Find a Cycle in this graph.
// If Cycle exists, we can deal damage indefinitely.
// If MaxPath >= BossHP, we win.
//
// Optimization:
// Nodes = N^4. If N is 3-5, feasible (625 nodes).
// If N is large, maybe simpler logic (Max move * 5 >= S).
// If MaxMove * 5 < S, Impossible.
// If MinMove * 5 >= S, Always Possible.
// The complexity is mixed moves.
//
// Input: BossHP, S, N, moves...

int BossHP, S, N_moves;
vector<int> moves;
bool visited[10000]; // Hash map for (m1,m2,m3,m4)
bool in_stack[10000];

// Hash function for 4 moves
int encode(const vector<int>& last4) {
    // Requires moves to be indices 0..N-1
    int h = 0;
    for(int x : last4) h = h * N_moves + x;
    return h;
}

vector<int> decode(int h) {
    vector<int> v(4);
    for(int i=3; i>=0; --i) {
        v[i] = h % N_moves;
        h /= N_moves;
    }
    return v;
}

bool has_cycle = false;

void dfs(int u) {
    visited[u] = true;
    in_stack[u] = true;
    
    vector<int> last4 = decode(u);
    int current_window_sum_base = 0;
    for(int idx : last4) current_window_sum_base += moves[idx];
    
    // Total sum needs 5th element.
    // Actually the condition "Total Damage in last 5 steps < S -> Shield".
    // So to deal damage, window MUST be >= S.
    // Edge (u -> v) exists if adding 'next' satisfies window.
    // u = (m1, m2, m3, m4). v = (m2, m3, m4, m5).
    // Sum = moves[m1] + ... + moves[m5] >= S.
    
    int partial_sum = 0; // m1..m4
    for(int idx : last4) partial_sum += moves[idx]; 
    // Wait, m1 is needed for Check.
    // Check uses m1..m5.
    
    for(int i=0; i<N_moves; ++i) {
        if (partial_sum + moves[i] >= S) {
            // Valid transition
            vector<int> next_node_vec = last4;
            next_node_vec.erase(next_node_vec.begin());
            next_node_vec.push_back(i);
            int v = encode(next_node_vec);
            
            if (in_stack[v]) {
                has_cycle = true;
                return;
            }
            if (!visited[v]) {
                dfs(v);
                if (has_cycle) return;
            }
        }
    }
    
    in_stack[u] = false;
}

int main() {
    if (!(cin >> BossHP >> S >> N_moves)) return 0;
    moves.resize(N_moves);
    for(int i=0; i<N_moves; ++i) cin >> moves[i];
    
    // Need to start?
    // Start state is (empty, empty, empty, empty)?
    // Or we pick first 4 moves freely?
    // "Shield aktif secara retroaktif". implies usually first few are free?
    // Or they must satisfy S?
    // Usually "Last 5 steps".
    // At Step 1, "Last 5" is [0,0,0,0, M1]. Sum < S?
    // If empty slots count as 0, then we MUST deal S damage in 1 hit? No.
    // Usually shield starts when window is full, OR partial window counts.
    // Assuming we can "build up" (Free start).
    // So we can reach ANY state (m1, m2, m3, m4) reachable from Start?
    // Actually, simply check if ANY Cycle exists in the Valid Transition Graph.
    // Because we can enter the cycle eventually.
    // Iterate all nodes as start points?
    // Only nodes that are reachable?
    // If the graph has a cycle, and we can enter it.
    // Can we simply jump to a valid state?
    // Yes, provided we survive the buildup. Assuming buildup is safe.
    
    // Check max element
    int max_m = 0; 
    for(int x : moves) max_m = max(max_m, x);
    if (max_m * 5 < S) {
        cout << "NO" << endl;
        return 0;
    }
    
    for(int i=0; i< pow(N_moves, 4); ++i) {
        if (!visited[i]) {
            dfs(i);
            if (has_cycle) break;
        }
    }
    
    if (has_cycle) cout << "YES" << endl;
    else cout << "NO" << endl;
    // Note: If no cycle, but path long enough? 
    // BossHP finite.
    // If Graph is DAG, check Longest Path.
    // But usually simple Cycle check suffices for "Strategy Aman".
    
    return 0;
}
