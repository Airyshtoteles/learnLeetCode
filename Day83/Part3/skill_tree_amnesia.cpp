#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

// Problem: Can we reach Target such that every prerequisite is consumed exactly once?
// Assumption: Skill dependencies are AND.
// Logic: The set of all required ancestors must be unique.
// If any node is required by two different paths, it would need to be consumed twice -> Impossible.

int main() {
    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<vector<int>> parents(N);
    for (int i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        // u -> v (u is parent of v)
        // We want to traverse from child to parent.
        parents[v].push_back(u);
    }

    int Target;
    cin >> Target;

    queue<int> q;
    q.push(Target);
    
    set<int> visited;
    visited.insert(Target);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int p : parents[u]) {
            if (visited.count(p)) {
                // Parent p is already required by someone else (or cycle)
                cout << "Impossible" << endl;
                return 0;
            }
            visited.insert(p);
            q.push(p);
        }
    }

    cout << "Possible" << endl;
    return 0;
}
