#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// Problem 3: Skill System With Gödel Lock
// Mechanics: 
// 1. A depends on B (Normal): Must take B before A.
// 2. A requires unprovability of B (Gödel): Must NEVER take B if A is effectively taken.
//    Logic: If we select A, we are committed to NOT selecting B.
//    If we select B, we cannot select A.
//    This is mutual exclusion (Conflict).
// Goal: Can we take T?
// Solution:
// 1. Identify all prerequisites of T (Recursively).
// 2. Identify all conflicts.
//    If X is in Prereq(T), and X conflicts with Y, then Y must be Forbidden.
//    Forbidden implies we cannot take Y.
// 3. Propagate Forbidden status backwards?
//    If Y is Forbidden (cannot be taken), then anything requiring Y (Z -> Y) is also Forbidden.
// 4. Check Consistency:
//    Is T Forbidden?
//    Is any Prereq(T) Forbidden?
//    Is there a conflict within Prereq(T)? (e.g. U, V in Prereq(T) and U conflicts V).

int main() {
    int N, M, K, T;
    // N skills, M deps (u -> v), K conflicts (u requires NOT v).
    if (!(cin >> N >> M >> K >> T)) return 0;
    
    vector<vector<int>> adj(N); // u depends on v
    vector<vector<int>> rev_adj(N); // v needed by u
    for(int i=0; i<M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    
    vector<vector<int>> conflicts(N); // u conflicts with v (u implies NOT v)
    for(int i=0; i<K; ++i) {
        int u, v;
        cin >> u >> v;
        conflicts[u].push_back(v);
        conflicts[v].push_back(u); // Mutual?
        // "A only if cannot be proven that B will ever be taken".
        // If we take A, B is forbidden.
        // If we take B, A is forbidden.
        // Yes, symmetric conflict.
    }
    
    // 1. Get Prerequisites of T
    set<int> prereqs;
    queue<int> q;
    q.push(T);
    prereqs.insert(T);
    
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(int v : adj[u]) {
            if(prereqs.find(v) == prereqs.end()){
                prereqs.insert(v);
                q.push(v);
            }
        }
    }
    
    // 2. Identify Forbidden
    set<int> forbidden;
    // Initial forbidden: if u in Prereqs, then all v colliding with u are forbidden.
    for(int u : prereqs) {
        for(int v : conflicts[u]) {
            forbidden.insert(v);
        }
    }
    
    // 3. Propagate Forbidden
    // If v is forbidden, then ANY node that requires v (w -> v) is also forbidden.
    // Use queue for propagation.
    queue<int> fq;
    for(int u : forbidden) fq.push(u);
    
    while(!fq.empty()){
        int u = fq.front(); fq.pop();
        
        // If u is forbidden, check who needs u.
        // These are in rev_adj[u].
        for(int w : rev_adj[u]) {
            if(forbidden.find(w) == forbidden.end()) {
                forbidden.insert(w);
                fq.push(w);
            }
        }
    }
    
    // 4. Check Consistency
    bool possible = true;
    for(int u : prereqs) {
        if(forbidden.count(u)) {
            possible = false;
            break;
        }
    }
    
    if(possible) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
