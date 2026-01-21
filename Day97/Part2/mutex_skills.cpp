#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// Problem 2: Skill Tree With Mutual Lock
// A and B can lock each other (Mutual Exclusion).
// If C is taken, A does NOT lock B?
// Structure:
// Nodes 1..N.
// Pairs (u, v) - Exclusive.
// Exceptions (u, v, unlocker).
// Energy Cost.
// Target T (or Maximize). Assuming Target T.
// N usually small for these logic puzzles. If N <= 20, bitmask DP.
// If N larger, check simple validity.
// "Inti: SAT". SAT implies complexity.
// Let's assume N <= 20.
// State: Mask of taken skills.
// Transitions:
// From Mask, try to take skill `i` (not in Mask).
// Check feasibility:
// 1. Costs: Energy >= Cost[i].
// 2. Dependencies? "Skill Tree". Assuming graph deps (parents). Mask must contain parents.
// 3. Locking:
//    For every already taken skill `j` in Mask:
//      Check if `i` and `j` are mutually locked.
//      If Locked(i, j):
//         Check if Unlocker(i, j) is in Mask.
//         If NOT, then invalid move.
//
// Target: Can we reach state where `TargetNode` is in Mask?
//
// Graph input:
// N, Energy.
// Costs.
// Parents (Adjacency).
// Locks: Pairs (u, v).
// Unlockers: Map Pair -> UnlockerNode. Or list.

int N;
int Costs[25];
int Parents[25]; // Bitmask of parents? Or List.
// Using Mask for Prerequisites checking.
int PrereqMask[25];
int TotalEnergy;
int TargetNode;

struct Lock {
    int u, v, unlocker;
};
vector<Lock> Locks;

bool visited[1 << 20];

// Memo? Just BFS on Mask.
// Or DFS.

bool can_take(int mask, int u) {
    // 1. Check Prereqs
    if ((mask & PrereqMask[u]) != PrereqMask[u]) return false;
    
    // 2. Check Locks
    for(const auto& l : Locks) {
        // If this lock involves u
        int other = -1;
        if (l.u == u) other = l.v;
        else if (l.v == u) other = l.u;
        
        if (other != -1) {
            // Check if 'other' is in mask
            if ((mask >> other) & 1) {
                // Conflict exists unless unlocker is present
                if (l.unlocker == -1) return false; // Hard lock
                if (!((mask >> l.unlocker) & 1)) return false; // Unlocker missing
            }
        }
    }
    return true;
}

int main() {
    // Input
    if (!(cin >> N >> TotalEnergy >> TargetNode)) return 0;
    
    for(int i=0; i<N; ++i) cin >> Costs[i];
    
    int num_deps; cin >> num_deps;
    for(int i=0; i<num_deps; ++i) {
        int u, p; cin >> u >> p;
        PrereqMask[u] |= (1 << p);
    }
    
    int num_locks; cin >> num_locks;
    for(int i=0; i<num_locks; ++i) {
        int u, v, k; cin >> u >> v >> k; // k is unlocker, or -1
        Locks.push_back({u, v, k});
    }
    
    // BFS
    // Queue of (Mask, CurrentEnergy)
    // Optimization: visited[mask] stores MaxEnergy remaining?
    // If we reach mask with less energy, ignore.
    // If we reach with more, update.
    
    vector<int> max_energy(1 << N, -1);
    vector<int> q;
    
    max_energy[0] = TotalEnergy;
    q.push_back(0);
    
    bool possible = false;
    int head = 0;
    
    while(head < q.size()) {
        int mask = q[head++];
        int e = max_energy[mask];
        
        if ((mask >> TargetNode) & 1) {
            possible = true;
            break;
        }
        
        // Try adding skills
        for(int i=0; i<N; ++i) {
            if (!((mask >> i) & 1)) {
                // Not taken
                if (e >= Costs[i]) {
                    if (can_take(mask, i)) {
                        int new_mask = mask | (1 << i);
                        int new_e = e - Costs[i];
                        
                        if (new_e > max_energy[new_mask]) {
                            if (max_energy[new_mask] == -1) q.push_back(new_mask);
                            max_energy[new_mask] = new_e;
                        }
                    }
                }
            }
        }
    }
    
    if (possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
