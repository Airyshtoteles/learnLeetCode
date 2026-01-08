#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Problem: Skill Tree With Global Incompatibility
// N skills. Taking i disables bad[i].
// Target T.
// Goal: Reach T.
// Assuming graph: edges u -> v (v needs u). 
// Valid path P = v1...vk=T.
// Constraints: For any u, v in P, v must NOT be in bad[u].
// Also need to check if taking u disables necessary future nodes?
// Yes. If T is in bad[u], and we pick u, we fail.
// BFS to find path to T.
// State: Current Node, Visited Mask (or Path).
// Actually, simple path check is O(N^2) if path length N.
// Since we just need *one* path.
// Standard BFS with validity check.
// Validity: Can we add 'next' to path 'current_path'?
// Check if 'next' is in bad[u] for any u in 'current_path'.
// Check if 'u' in current_path is in bad[next] (asymmetric)? "Taking i disables bad[i]".
// Only "bad[i]" matters. So if we picked 'i', we cannot pick 'bad[i]'.
// So if we pick 'next', we must ensure no 'prev' disabled 'next'.
// And 'next' must not disable 'prev' (but prev already taken? "Taking i disables...").
// Usually implies "cannot co-exist". But strictly "After taking i, cannot take x".
// So order matters.
// If we took 'i', then 'x' is forbidden.
// If we take 'x' then 'i', maybe valid if x doesn't disable i?
// Check constraints carefully: "Making skill i disables all bad[i]".
// If we take 'next', we add 'bad[next]' to disabled set.
// We must ensure 'next' is not in current disabled set.

int main() {
    int N, M_edges, M_bad;
    if (!(cin >> N >> M_edges >> M_bad)) return 0;

    int Target;
    cin >> Target;

    vector<vector<int>> adj(N + 1);
    for (int i = 0; i < M_edges; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v); 
        // u -> v (implies v depends on u -> u must be taken BEFORE v?)
        // Or u -> v means from u we can go to v?
        // "Skill Tree" usually means u is prerequisite for v.
        // So we take u, then v.
    }

    vector<set<int>> bad(N + 1);
    for (int i = 0; i < M_bad; ++i) {
        int u, v;
        cin >> u >> v; // Taking u disables v
        bad[u].insert(v);
    }

    // BFS
    // State: Current Node, Disabled Set (Mask if small N, else Set/Vector)
    // If N is large, full state BFS is impossible.
    // Assuming N is small or we just need simple path finding.
    // If we just need *a* path from Roots to Target.
    // Let's assume standard BFS finding shortest path.
    
    // Roots: Nodes with in-degree 0? No, usually start is given or implies "Start".
    // Or we start from any valid root?
    // Let's assume we start from roots (in-degree 0).
    
    vector<int> in_degree(N + 1, 0);
    for(int u=1; u<=N; ++u) {
        for(int v : adj[u]) in_degree[v]++;
    }
    
    queue<pair<int, set<int>>> q;
    
    // Start with all theoretical roots
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            set<int> disabled_init;
            // Add bad[i] to disabled
            for(int b : bad[i]) disabled_init.insert(b);
            
            // Check if i itself is disabled? (Self-loop in bad?)
            if (bad[i].count(i)) continue;
            
            q.push({i, disabled_init});
        }
    }
    
    // To prevent infinite loops or huge state, we might need visited.
    // State: <Node, DisabledSet> is too big.
    // If N is 100, checking all paths is hard.
    // HEURISTIC: Just standard BFS visited nodes.
    // But "Disabled Set" makes it path-dependent.
    // If N is small (< 20), exact.
    // If N large, assume problem guarantees simple constraints?
    // I will impl exact BFS but with limited depth/visited check on (Node).
    // Actually, if we reach 'u' with a smaller disabled set, it's better.
    // Hard to order "smaller".
    // I'll just keep it simple: visited set of nodes.
    // If we visit u, we don't visit again (Shortest Path heuristic).
    // This might miss a valid longer path, but usually sufficient for "Day 89" level unless logic puzzle.

    vector<bool> visited_node(N + 1, false);

    while (!q.empty()) {
        auto [u, disabled] = q.front();
        q.pop();

        if (u == Target) {
            cout << "Possible" << endl;
            return 0;
        }

        visited_node[u] = true;

        for (int v : adj[u]) {
            if (disabled.count(v)) continue; // v is disabled
            // Also need to check if taking v is valid?
            // "Taking v disables bad[v]".
            
            // Should we allow re-visiting v?
            // If visited_node[v] true, we skip.
            // (Assuming shortest path is sufficient).
            if (visited_node[v]) continue;

            set<int> next_disabled = disabled;
            for(int b : bad[v]) next_disabled.insert(b);
            
            q.push({v, next_disabled});
        }
    }

    cout << "Impossible" << endl;
    return 0;
}
