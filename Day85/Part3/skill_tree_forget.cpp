#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// Problem: Skill Tree With Mutual Forgetting
// Taking skill u removes all skills that are NOT (ancestor of u OR descendant of u).
// To reach Target T, we must take a sequence of skills.
// Each skill taken must preserve the ability to take the next.
// This implies that for any two skills A and B required for T (where A is taken before B),
// B must be a descendant of A (or A ancestor of B).
// If B is not related to A, taking A removes B.
// Thus, all ancestors of T must form a linear chain.
// If T has multiple parents, say P1 and P2, and P1 is not ancestor of P2 (and vice versa),
// then taking P1 removes P2. We can never take T.
// So, the set of all ancestors of T must be totally ordered by the ancestor relationship.
// Algorithm:
// 1. Find all ancestors of T.
// 2. Check if they form a chain.
//    Count ancestors. Sort them by topological order (or just depth/count of their ancestors).
//    Check if A[i] is parent of A[i+1].

vector<vector<int>> adj;
vector<vector<int>> rev_adj;
vector<bool> is_ancestor;
vector<int> ancestors;

void find_ancestors(int u) {
    if (is_ancestor[u]) return;
    is_ancestor[u] = true;
    ancestors.push_back(u);
    for (int p : rev_adj[u]) {
        find_ancestors(p);
    }
}

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    adj.resize(N + 1);
    rev_adj.resize(N + 1);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }

    int Target;
    cin >> Target;

    is_ancestor.assign(N + 1, false);
    // Don't include Target in ancestors list for checking parents, but logic applies to all nodes in path.
    // Actually, let's include Target.
    find_ancestors(Target);

    // Check if ancestors form a chain.
    // A set of nodes forms a chain in a DAG if for every pair u, v, either u->...->v or v->...->u.
    // Or simply, sort by number of ancestors.
    // If it's a chain, the one with k ancestors must be parent of the one with k+1 ancestors.
    
    // Let's compute ancestor count for each node in the set.
    // But that's slow O(N^2).
    // Better: The subgraph induced by ancestors must be a line.
    // In a line, every node has at most 1 parent (in the induced subgraph) and 1 child.
    // The root has 0 parents, Target has 0 children (in ancestors set).
    // So, check in-degree and out-degree within the set.
    
    for (int u : ancestors) {
        int in_degree = 0;
        for (int p : rev_adj[u]) {
            if (is_ancestor[p]) {
                in_degree++;
            }
        }
        if (in_degree > 1) {
            cout << "Impossible" << endl;
            return 0;
        }
    }

    cout << "Possible" << endl;

    return 0;
}
