#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// Problem 3: Skill Graph With Expiring Nodes
// Determine if a schedule exists to reach Target T given deadlines.
// Each node takes 1 unit time.
// Dependencies must be completed before node.
// All tasks involved must complete before their T[u].
// Strategy: Backward scheduling.
// 1. Identify all ancestors of T (Relevant nodes).
// 2. Compute "Latest Start Time" or equivalent Deadline for feasibility.
// 3. For a set of tasks S with deadlines D[u]:
//    Can we schedule them 0..|S|-1 such that finish_time(u) <= D[u]?
//    Finish time of k-th task is k+1.
//    Condition: (k+1) <= D[u] -> k <= D[u]-1.
//    Actually simpler: Sort tasks by D[u].
//    Check if i+1 <= D[sorted[i]].
//    Wait. Topology matters. We must respect dependencies.
//    We can only execute a node if its deps are done.
//    If we just consider the set of necessary nodes S.
//    Does a valid topological sort satisfy deadlines?
//    Heuristic: "Earliest Deadline First" on AVAILABLE nodes.
//    Algorithm:
//      - Compute set S (Ancestors of T + T).
//      - Simulation: t = 1.
//      - Available Queue (Nodes with in-degree 0 within S).
//      - Pick from Available: Node with smallest D[u].
//      - Check if t <= D[u] (actually finish time is t. So t <= D[u]).
//      - If yes, t++. Add children to queue.
//      - If no or queue empty before T done, Fail.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;
    
    vector<int> expiry(N + 1);
    for(int i=1; i<=N; ++i) cin >> expiry[i];
    
    vector<vector<int>> adj(N + 1);
    vector<vector<int>> rev_adj(N + 1);
    vector<int> in_degree(N + 1, 0);
    
    for(int i=0; i<M; ++i){
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u); // For finding ancestors
        in_degree[v]++;
    }
    
    int Target;
    cin >> Target;
    
    // Step 1: Identify Relevant Nodes (Ancestors of Target)
    // BFS backwards from Target
    vector<bool> relevant(N + 1, false);
    queue<int> q;
    q.push(Target);
    relevant[Target] = true;
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int p : rev_adj[u]){
            if(!relevant[p]){
                relevant[p] = true;
                q.push(p);
            }
        }
    }
    
    // Recompute in-degrees for subgraph of relevant nodes
    vector<int> sub_in_degree(N + 1, 0);
    int count_relevant = 0;
    for(int i=1; i<=N; ++i){
        if(relevant[i]){
            count_relevant++;
            for(int v : adj[i]){
                if(relevant[v]){
                    sub_in_degree[v]++;
                }
            }
        }
    }
    
    // Step 2: Simulation with Priority Queue (Min Deadline)
    // Queue stores {Expiry, ID}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    for(int i=1; i<=N; ++i){
        if(relevant[i] && sub_in_degree[i] == 0){
            pq.push({expiry[i], i});
        }
    }
    
    int current_time = 1;
    int processed_count = 0;
    
    while(!pq.empty()){
        auto [deadline, u] = pq.top();
        pq.pop();
        
        // Check deadline
        if (current_time > deadline) {
            cout << "NO" << endl;
            return 0;
        }
        
        current_time++;
        processed_count++;
        
        if (u == Target) {
            cout << "YES" << endl;
            return 0;
        }
        
        for(int v : adj[u]){
            if(relevant[v]){
                sub_in_degree[v]--;
                if(sub_in_degree[v] == 0){
                    pq.push({expiry[v], v});
                }
            }
        }
    }
    
    // Fallback if loop finishes without hitting Target (shouldn't happen if relevant logic correct)
    if (processed_count == count_relevant) cout << "YES" << endl; // Should have hit T
    else cout << "NO" << endl;
    
    return 0;
}
