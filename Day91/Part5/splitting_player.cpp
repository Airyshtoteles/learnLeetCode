#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 5: Player That Splits Into All Futures
// Rule: Move to ALL neighbors.
// Win if ONE branch reaches Target.
// Lose if ALL branches die.
// Interpretation: Start S. Set of active node {S}.
// Step: {S'} = Union(Neighbors(u) for u in {S}).
// If T in {S'}, Win.
// If {S'} is empty, Lose.
// Valid strategy?
// This is strictly deterministic.
// Just need Reachability from Start to Target.
// BFS to check if T is reachable.

int main() {
    int N, M, Start, Target;
    if (!(cin >> N >> M >> Start >> Target)) return 0;
    
    vector<vector<int>> adj(N);
    for(int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        // Directed or Undirected? "Graph". Movement usually directed "steps".
        // Part 2 was "Graph" too.
        // If directed, u -> v.
        // Assuming directed.
    }
    
    queue<int> q;
    q.push(Start);
    vector<bool> visited(N, false);
    visited[Start] = true;
    
    bool possible = false;
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        if(u == Target) {
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
