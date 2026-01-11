#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 2: Dungeon With Collapsing Reachability
// Uncertainty: Assumed we must beat the worst-case assignment of timers.
// Input: N (nodes), M (edges), Start, Target.
//        Then N integers (Timers).
// Task: Is there a path of length L such that
//       Steps to k-th node < k-th smallest Timer?
//       Essentially, sort Timers T_1 <= T_2 <= ...
//       Path nodes v_1, v_2, ..., v_L.
//       Adversary assigns min timers to these steps.
//       We need: At step i (arrival time), Timer assigned T_(?) > i.
//       Assuming one timer per node used.
//       If path length is L, we use L nodes (excluding start? including target?).
//       Assume Start is safe (Time 0).
//       Path: Start -> v1 -> v2 ... -> Target (length L edges).
//       v1 reached at t=1. Needs T > 1.
//       v2 reached at t=2. Needs T > 2.
//       Assignment: Adversary assigns smallest T to v1?
//       Yes. To block us earliest.
//       So we need sorted_timers[0] > 1, sorted_timers[1] > 2, ...
//       Condition: For all k in 1..L, sorted_timers[k-1] > k.
//       If this holds for shortest path length L, return YES.

int main() {
    int N, M, Start, Target;
    if (!(cin >> N >> M >> Start >> Target)) return 0;
    
    // Read Timers
    vector<int> Timers(N);
    for(int i=0; i<N; ++i) cin >> Timers[i];
    
    sort(Timers.begin(), Timers.end());
    
    // Read Graph
    vector<vector<int>> adj(N);
    for(int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // Undirected? assumed dungeon usually undirected unless specified.
        // Prompt says "Dungeon ... Graph". Usually directed or undirected? 
        // "Grid" was previous. "Graph" now.
        // Assuming Undirected for Dungeon topology? Or Directed?
        // Let's assume Directed as standard for "Graph". 
        // If "Dungeon" implies walking, usually undirected. 
        // But let's assume Directed to be safe with input like "u v".
        // Wait, standard for these usually undirected if not specified.
        // I will assume Directed for general graph.
        // Actually, if input is u v, often undirected.
        // I'll make it Undirected as safe bet for "Dungeon".
        // Re-reading: "Graph". "Node tidak bisa dilewati".
        // I'll stick to Undirected.
    }

    // BFS for shortest path
    vector<int> dist(N, -1);
    queue<int> q;
    
    q.push(Start);
    dist[Start] = 0;
    
    int path_len = -1;
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(u == Target){
            path_len = dist[Target];
            break;
        }
        
        for(int v : adj[u]){
            if(dist[v] == -1){
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    if(path_len == -1) {
        cout << "NO" << endl;
        return 0;
    }
    
    // Check worst case
    // We visit path_len nodes (excluding start).
    // Start is at t=0. Next node t=1.
    // We consume 'path_len' timers.
    // Adversary assigns smallest 'path_len' timers to our path nodes.
    // We need Timers[k] > (k+1) for k=0..path_len-1.
    // Arrival at k-th step is time k+1.
    // i.e., at step 1 (arrival), timer must be > 1.
    
    bool ok = true;
    for(int i=0; i<path_len; ++i) {
        if(i >= Timers.size()) { ok = false; break; }
        if(Timers[i] <= (i + 1)) {
            ok = false;
            break;
        }
    }
    
    if(ok) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
