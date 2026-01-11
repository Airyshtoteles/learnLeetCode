#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Problem 3: Skill DAG With Anti-Monotone Unlock
// Rule: Taking a skill locks all ancestors, unlocks all descendants.
// Target T.
// Interpretation: We need a valid sequence of skills ending in T.
// Due to "Locks Ancestors", taking a node essentially consumes the branch.
// Effective Constraint: Can we find a simple path from a Root (initially unlocked) to T?
// If yes, following the path works:
//   Start at Root (Unlocked).
//   Take Root. Unlocks Children. Locks nothing (no ancestors).
//   Take Child. Unlocks Grandchildren. Locks Root (which is done).
//   ...
//   Take T.
// This valid path logic holds for trees and DAGs if we stick to one lineage.
// If T requires multiple parents (AND logic), it's impossible because taking one parent locks its grandparent which might be needed?
// Actually if parents are disjoint, fine.
// But prompt implies "Unlocks ALL descendants". This usually suggests OR logic for availability.
// i.e., IF (Parent A taken OR Parent B taken) -> Child C unlocked.
// If so, Reachability check is sufficient.

int main() {
    int N, M, T;
    if (!(cin >> N >> M >> T)) return 0;
    
    vector<vector<int>> adj(N);
    vector<int> in_degree(N, 0);
    
    for(int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        in_degree[v]++;
    }
    
    // BFS from Roots (in-degree 0)
    queue<int> q;
    vector<bool> visited(N, false);
    
    for(int i=0; i<N; ++i) {
        if(in_degree[i] == 0) {
            q.push(i);
            visited[i] = true;
        }
    }
    
    bool possible = false;
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(u == T) {
            possible = true;
            break;
        }
        
        for(int v : adj[u]) {
            if(!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    
    if(possible) cout << "YES" << endl;
    else cout << "NO" << endl;
    
    return 0;
}
